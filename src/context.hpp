#pragma once

#include <map>
#include <utility>
#include <memory>
#include <functional>
#include <array>
#include "types.hpp"

using Label = std::string;

using Offset = unsigned int;

enum class IntRegister : short int {
    v0 = 2, v1 = 3,
    a0, a1, a2, a3,
    t0, t1, t2, t3, t4, t5, t6, t7,
    s0, s1, s2, s3, s4, s5, s6, s7,
    t8, t9,
    k0, k1,
    gp, sp, fp, ra = 31
};
std::string to_string(IntRegister reg);

enum class FpRegister : short int{
    f0=0, f1=1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16,
    f17, f18, f19, f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, f30
};
std::string to_string(FpRegister reg);

class UndeclaredVariable : public std::exception {
    public:
        const std::string variable_name;
        const char* what() const noexcept override {
            return (variable_name + " is not declared").c_str();
        }
        UndeclaredVariable(std::string _variable_name) noexcept
            : variable_name(_variable_name) {};
};

class VariableRedeclaration : public std::exception {
    public:
        const std::string variable_name;
        const char* what() const noexcept override {
            return (variable_name + " is already declared").c_str();
        }
        VariableRedeclaration(std::string _variable_name) noexcept
            : variable_name(_variable_name) {};
};

class NoAvailableRegisters : public std::exception {
    public:
        const std::string which_registers;
        const char* what() const noexcept override {
            return ("All " + which_registers + " registers are taken").c_str();
        }
        NoAvailableRegisters(std::string _which_registers) noexcept
            : which_registers(_which_registers) {};
};

/**
 * Contains info about location of a variable.
 * Implemented as a tagged union.
 *
 * Default constructor is deleted, use the make_* static methods
 *
 * use `match` get the contained location information
 */
class LocationInfo {
    private:
        enum LocationType { IN_FLOAT, IN_INTEGER, IN_MEMORY } location_type;
        union {
            FpRegister fp_register;
            IntRegister int_register;
            Offset offset;
        };

    public:
        LocationInfo(FpRegister) noexcept;
        LocationInfo(IntRegister) noexcept;
        LocationInfo(Offset) noexcept;

        static LocationInfo make_int_register(unsigned int) noexcept;
        static LocationInfo make_fp_register(unsigned int) noexcept;
        static LocationInfo make_offset(Offset) noexcept;

        LocationInfo(const LocationInfo& other)
            : location_type(other.location_type) {
                other.match(
                    [&] (auto reg)  { int_register = reg; },
                    [&] (auto reg)  { fp_register = reg; },
                    [&] (auto _offset) { offset = _offset; });
        }

        /**
         * Discriminate between possible locations
         * Accepts three function arguments, the one called depends on whether
         * the location is in integer registers, floating point registers,
         * or memory.
         */
        void match(const std::function<void (IntRegister)>& int_register_case,
                   const std::function<void (FpRegister)>& fp_register_case,
                   const std::function<void (Offset)>&  address_case) const;
};

struct StorageInfo {
    LocationInfo location;
    std::shared_ptr<const Type> type;
};

/**
 * Contains info about compilation context and allocates variables
 *
 * parent: parent context to which this belongs. Could be nullptr
 * variables: map to variable info for available variables. Use `lookup_variable` to query
 */
class Context {
    private:
        struct VariableInfo {
            std::string name;
            enum Volatility {
                STATIC, TEMPORARY, PERSISTENT
            } volatility;
            std::shared_ptr<const Type> type;

            VariableInfo(std::string _name, Volatility _volatility,
                         std::shared_ptr<const Type> _type)
                : name(_name), volatility(_volatility), type(_type){};
        };

        std::shared_ptr<const Context> parent;

        /**
         * Used to csupply new labels.
         */
        unsigned int label_index = 0;

        /**
         * Used to track how much space is required for the stack frame
         */
        unsigned int max_stack_size = 0;

        std::map<Offset, VariableInfo> stack;
        std::map<std::string, VariableInfo> static_vars;
        std::map<std::string, std::pair<VariableInfo, LocationInfo>> arguments;
        std::array<std::unique_ptr<VariableInfo>, 32> int_registers;
        std::array<std::unique_ptr<VariableInfo>, 32> fp_registers;

        std::unique_ptr<VariableInfo>& register_at(IntRegister);
        std::unique_ptr<VariableInfo>& register_at(FpRegister);

        Offset find_stack_location(const Type&);
        LocationInfo find_persistent_location(const Type&);
        LocationInfo find_temporary_location(const Type&);

      public:
        Context(std::shared_ptr<Context> parent) noexcept;
        Context() noexcept;

        StorageInfo lookup_local_variable(std::string) const;
        StorageInfo lookup_variable(std::string) const;

        LocationInfo allocate_persistent(std::string name,
                                         std::shared_ptr<const Type> type);
        LocationInfo allocate_temporary(std::string name,
                                        std::shared_ptr<const Type> type);
        Label allocate_static(std::string name, std::shared_ptr<const Type> type);
        Offset allocate_stack(std::string name, std::shared_ptr<const Type> type);

        /**
         * Add an argument to the Context. A type and a location have to be
         * specified. Note, that in the location, the offset case now refers to
         * an offset from the top of the stack frame, i.e. the beginning of the
         * stack arguments area.
         *
         *  | 2nd stack argument    | <- offset 4
         *  | 1st stack argument    | <- offset 0
         *  |-----------------------|
         *  | current stack frame   |
         *  | ...                   |
         *
         */
        void add_argument(std::string name, std::shared_ptr<const Type>,
                          LocationInfo);

        void free(std::string name);

        /**
         * Get the maximum size the would be required for this function context.
         * To be used by the function compiler as a stack frame size.
         *
         * In bytes.
         */
        unsigned int get_max_stack_size() const { return max_stack_size; };

        /**
         * Get a fresh label in the form "L{n}"
         */
        std::string new_label() {
            return "L"+std::to_string(label_index++);
        }
};
