#include <algorithm>
#include <utility>
#include "context.hpp"
#include "util.hpp"

using namespace std;

string to_string(IntRegister reg) {
    switch(reg) {
        case IntRegister::v0: return "$v0";
        case IntRegister::v1: return "$v1";
        case IntRegister::a0: return "$a0";
        case IntRegister::a1: return "$a1";
        case IntRegister::a2: return "$a2";
        case IntRegister::a3: return "$a3";
        case IntRegister::t0: return "$t0";
        case IntRegister::t1: return "$t1";
        case IntRegister::t2: return "$t2";
        case IntRegister::t3: return "$t3";
        case IntRegister::t4: return "$t4";
        case IntRegister::t5: return "$t5";
        case IntRegister::t6: return "$t6";
        case IntRegister::t7: return "$t7";
        case IntRegister::s0: return "$s0";
        case IntRegister::s1: return "$s1";
        case IntRegister::s2: return "$s2";
        case IntRegister::s3: return "$s3";
        case IntRegister::s4: return "$s4";
        case IntRegister::s5: return "$s5";
        case IntRegister::s6: return "$s6";
        case IntRegister::s7: return "$s7";
        case IntRegister::t8: return "$t8";
        case IntRegister::t9: return "$t9";
        case IntRegister::k0: return "$k0";
        case IntRegister::k1: return "$k1";
        case IntRegister::gp: return "$gp";
        case IntRegister::sp: return "$sp";
        case IntRegister::fp: return "$fp";
        case IntRegister::ra: return "$ra";
    }
}

string to_string(FpRegister reg) {
    switch(reg) {
        case FpRegister::f0: return "$f0";
        case FpRegister::f1: return "$f1";
        case FpRegister::f2: return "$f2";
        case FpRegister::f3: return "$f3";
        case FpRegister::f4: return "$f4";
        case FpRegister::f5: return "$f5";
        case FpRegister::f6: return "$f6";
        case FpRegister::f7: return "$f7";
        case FpRegister::f8: return "$f8";
        case FpRegister::f9: return "$f9";
        case FpRegister::f10: return "$f10";
        case FpRegister::f11: return "$f11";
        case FpRegister::f12: return "$f12";
        case FpRegister::f13: return "$f13";
        case FpRegister::f14: return "$f14";
        case FpRegister::f15: return "$f15";
        case FpRegister::f16: return "$f16";
        case FpRegister::f17: return "$f17";
        case FpRegister::f18: return "$f18";
        case FpRegister::f19: return "$f19";
        case FpRegister::f20: return "$f20";
        case FpRegister::f21: return "$f21";
        case FpRegister::f22: return "$f22";
        case FpRegister::f23: return "$f23";
        case FpRegister::f24: return "$f24";
        case FpRegister::f25: return "$f25";
        case FpRegister::f26: return "$f26";
        case FpRegister::f27: return "$f27";
        case FpRegister::f28: return "$f28";
        case FpRegister::f29: return "$f29";
        case FpRegister::f30: return "$f30";
    }
}

LocationInfo LocationInfo::make_fp_register(unsigned int reg) noexcept {
    return LocationInfo(static_cast<FpRegister>(reg));
}

LocationInfo LocationInfo::make_int_register(unsigned int reg) noexcept {
    return LocationInfo(static_cast<IntRegister>(reg));
}

LocationInfo LocationInfo::make_offset(Offset offset) noexcept {
    return LocationInfo(static_cast<Offset>(offset));
}

LocationInfo::LocationInfo(IntRegister reg) noexcept
    : location_type(IN_INTEGER), int_register(reg) {};

LocationInfo::LocationInfo(FpRegister reg) noexcept
    : location_type(IN_FLOAT), fp_register(reg) {};

LocationInfo::LocationInfo(Offset offset) noexcept
    : location_type(IN_MEMORY), offset(offset) {};

void LocationInfo::match(const std::function<void (IntRegister)>& int_register_case,
                         const std::function<void (FpRegister)>& fp_register_case,
                         const std::function<void (Offset)>&  offset_case) const {
    switch (location_type) {
        case IN_INTEGER:
            int_register_case(int_register);
            return;
        case IN_FLOAT:
            fp_register_case(fp_register);
            return;
        case IN_MEMORY:
            offset_case(offset);
            return;
    }
}

Context::Context(std::shared_ptr<Context> _parent) noexcept
    : parent(_parent) {};

Context::Context() noexcept
    : parent(nullptr) {};

unique_ptr<Context::VariableInfo>& Context::register_at(IntRegister reg) {
    return int_registers[static_cast<underlying_type_t<IntRegister>>(reg)];
}
unique_ptr<Context::VariableInfo>& Context::register_at(FpRegister reg) {
    return fp_registers[static_cast<underlying_type_t<FpRegister>>(reg)];
}

Offset Context::find_stack_location(const Type& type) {
    unsigned int bytes_required = type.get_type_info().size_bytes;

    // Beginning of the stack
    if (stack.begin() == stack.end()) {
        return 0;
    }

    // Inside the stack
    for (auto it = stack.begin(); it != --stack.end(); ++it) {
        Offset space_begin =
            it->first + // Begining of element
            it->second.type->get_type_info().size_bytes; // Size of element

        int bytes_available =
            next(it)->first - // Beginning of next element
            space_begin; // End of current element

        if (bytes_required <= bytes_available) {
            return word_align(space_begin);
        }
    }

    // End of the stack
    return word_align(
        prev(stack.end())->first + // begining of last element
        prev(stack.end())->second.type->get_type_info().size_bytes); // size of last element
}

LocationInfo Context::find_persistent_location(const Type& type) {
    int bytes_required = type.get_type_info().size_bytes;

    auto div_round_up = [](int x, int y) {
        return (x/y) + (x%y != 0 ? 1 : 0);
    };

    // If it should be in registers
    if (bytes_required <= 8) {
        if (type.get_type_info().in_fp_reg) { // fp register
            for (int i=20; i <= (31 - div_round_up(bytes_required, 4)); ++i) {
                // Check if it fits in this spot
                bool fits = true;
                for (int j = 0; j <= bytes_required; ++j) {
                    if (fp_registers[i+j] != nullptr) {
                        fits = false;
                        break;
                    }
                }
                if (fits)
                    return LocationInfo::make_fp_register(i);
            }
        } else { // int register
            for (int i=16; i <= (23 - div_round_up(bytes_required, 4)); ++i) {
                // Check if it fits in this spot
                bool fits = true;
                for (int j = 0; j <= bytes_required; ++j) {
                    if (int_registers[i+j] != nullptr) {
                        fits = false;
                        break;
                    }
                }
                if (fits)
                    return LocationInfo::make_int_register(i);
            }
        }
    }

    // No register space
    return LocationInfo::make_offset(find_stack_location(type));
}

LocationInfo Context::find_temporary_location(const Type& type) {
    auto& registers = type.get_type_info().in_fp_reg ? fp_registers : int_registers;
    int reg_begin   = type.get_type_info().in_fp_reg ? 4            : 8;
    int reg_end     = type.get_type_info().in_fp_reg ? 11           : 16;

    for (int i = reg_begin; i < reg_end; ++i) {
        if (registers[i] == nullptr) {
            if (type.get_type_info().in_fp_reg) {
                return LocationInfo::make_fp_register(i);
            } else {
                return LocationInfo::make_int_register(i);
            }
        }
    }

    throw NoAvailableRegisters(type.get_type_info().in_fp_reg ? "floating point" : "integer");
}

StorageInfo Context::lookup_local_variable(std::string name) const {
    // Search integer registers
    for (int i = 0; i < int_registers.size(); ++i) {
        if (int_registers.at(i) && int_registers.at(i)->name == name) {
            return {
                LocationInfo::make_int_register(i),
                int_registers.at(i)->type
            };
        }
    }

    // Search fp registers
    for (int i = 0; i < fp_registers.size(); ++i) {
        if (fp_registers.at(i) && fp_registers.at(i)->name == name) {
            return {
                LocationInfo::make_fp_register(i),
                fp_registers.at(i)->type
            };
        }
    }

    // Search arguments
    try {
        pair<VariableInfo, LocationInfo> arg = arguments.at(name);
        arg.second.match(
            [&] (IntRegister reg) {},
            [&] (FpRegister freg) {},
            [&] (Offset offset) { throw runtime_error("Can't handle stack arguments"); });

        return {arg.second, arg.first.type};

    } catch (const out_of_range& err) {}

    // Search stack
    for (auto it = stack.begin(); it != stack.end(); ++it) {
        if (it->second.name == name) {
            return {
                LocationInfo::make_offset(it->first),
                it->second.type
            };
        }
    }

    throw UndeclaredVariable(name);
}

StorageInfo Context::lookup_variable(std::string name) const {
    try {
        return lookup_local_variable(name);
    } catch (const UndeclaredVariable& err) {
        if (parent) {
            return parent->lookup_variable(name);
        }
        throw err;
    }
}


Label Context::allocate_static(std::string name, std::shared_ptr<const Type> type) {
    try {
        lookup_local_variable(name);
        throw VariableRedeclaration(name);
    } catch (const UndeclaredVariable&) {}

    static_vars.emplace(name, VariableInfo(name, VariableInfo::STATIC, type));

    return name;
}

LocationInfo Context::allocate_persistent(std::string name, std::shared_ptr<const Type> type) {
    try {
        lookup_local_variable(name);
        throw VariableRedeclaration(name);
    } catch (const UndeclaredVariable&) {}

    LocationInfo location = find_persistent_location(*type);
    location.match(
        [&] (IntRegister reg)  {
            register_at(reg) = make_unique<VariableInfo>(name, VariableInfo::PERSISTENT, type);
        },
        [&] (FpRegister reg)  {
            register_at(reg) = make_unique<VariableInfo>(name, VariableInfo::PERSISTENT, type);
        },
        [&] (Offset addr) {
            stack.emplace(addr, VariableInfo(name, VariableInfo::PERSISTENT, type));
        });

    return location;
}

Offset Context::allocate_stack(std::string name, std::shared_ptr<const Type> type) {
    try {
        lookup_local_variable(name);
        throw VariableRedeclaration(name);
    } catch (const UndeclaredVariable&) {}

    Offset offset = find_stack_location(*type);
    stack.emplace(offset, VariableInfo(name, VariableInfo::PERSISTENT, type));

    // Increase max stack size if necessary
    max_stack_size = max(max_stack_size, offset+type->get_type_info().size_bytes);

    return offset;
}

void Context::add_argument(std::string name, std::shared_ptr<const Type> type, LocationInfo location) {
    arguments.emplace(name,
                      make_pair(VariableInfo(name, VariableInfo::PERSISTENT, type),
                                location));
}

LocationInfo Context::allocate_temporary(std::string name, std::shared_ptr<const Type> type) {
    try {
        lookup_local_variable(name);
        throw VariableRedeclaration(name);
    } catch (const UndeclaredVariable&) {}

    LocationInfo location = find_temporary_location(*type);
    location.match(
        [&] (IntRegister reg)  {
            register_at(reg) =
                make_unique<VariableInfo>(name, VariableInfo::TEMPORARY, type);
        },
        [&] (FpRegister reg)  {
            register_at(reg) =
                make_unique<VariableInfo>(name, VariableInfo::TEMPORARY, type);
        },
        [&] (Offset offset) {
            stack.emplace(offset, VariableInfo(name, VariableInfo::TEMPORARY, type));
        });

    return location;
}
