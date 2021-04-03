TEST_CC=../bin/c_compiler
MIPS_CC=mips-linux-gnu-gcc
MIPS_CCFLAGS=-mfp32 -static

compile_src=$(wildcard compilation/*.c)
compile_asm=$(compile_src:compilation/%.c=compilation_results/%.mips.s)
compile_obj=$(compile_asm:.s=.o)
compile_bin=$(compile_asm:.s=.bin)
compile_gcc_asm=$(compile_src:compilation/%.c=compilation_results/gcc/%.mips.s)
compile_gcc_bin=$(compile_src:compilation/%.c=compilation_results/gcc/%.mips.bin)
.PRECIOUS: $(compile_asm) $(compile_obj) $(compile_gcc_asm)

translate_src=$(wildcard python_translation/*.c)
translate_py=$(translate_src:python_translation/%.c=python_translation_results/%.py)
.PRECIOUS: $(translate_py)

all: compilation_tests translation_tests
clean: clean_compilation_tests clean_translation_tests

compilation_tests: $(compile_bin) $(compile_gcc_bin)
clean_compilation_tests:
	rm -rf python_translation_results

translation_tests:
clean_translation_tests:
	rm -rf compilation_results

compilation_results/%.mips.s: compilation/%.c compilation_results_dir $(TEST_CC)
	$(TEST_CC) -S $< -o $@

compilation_results/gcc/%.mips.s: compilation/%.c compilation_results_dir
	$(MIPS_CC) $(MIPS_CCFLAGS) -S -o $@ $<

%.mips.o: %.mips.s
	$(MIPS_CC) $(MIPS_CCFLAGS) -o $@ -c $<

%.mips.bin: %.mips.o
	$(MIPS_CC) $(MIPS_CCFLAGS) -o $@ $<

python_translation_results/%.py: python_translation/%.c translation_results_dir $(TEST_CC)
	$(TEST_CC) --translate $< -o $@

compilation_results_dir:
	mkdir -p compilation_results/gcc

translation_results_dir:
	mkdir -p python_translation_results
