##	HELPER FILES
include	./includes/make/vars.mk

norm:
	@truncate -s 0 ${NORM_LOGS}
	@for dir in ${NORM_DIRS}; do \
		echo "Norminette: $$dir" >> ${NORM_LOGS}; \
		total_files=$$(find $$dir -type f | wc -l); \
		norm_output=$$(norminette $$dir | sed 's/^/\t/'); \
		echo "$$norm_output" >> ${NORM_LOGS}; \
		error_files=$$(echo "$$norm_output" | grep -c "Error!"); \
		total_errors=$$(echo "$$norm_output" | grep -c "Error:"); \
		if [ $$total_errors -gt 0 ]; then \
			printf "\t%-28s ${C_RED}[KO]${RESET_ALL} (%d of %d files checked. %d errors found in %d files)\n" $$dir $$total_files $$total_files $$total_errors $$error_files; \
		else \
			printf "\t%-28s ${C_GREEN}[OK]${RESET_ALL} (%d of %d files checked. %d errors found in %d files)\n" $$dir $$total_files $$total_files 0 0; \
		fi; \
		echo >> ${NORM_LOGS}; \
	done

run: re
	${VALGRIND} ${VALGRIND_LOGS} ${BIN_DIR}/${NAME}