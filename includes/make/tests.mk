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
			printf "%-28s ${C_RED}[KO]${RESET_ALL} (%d of %d files checked. %d errors found in %d files)\n" $$dir $$total_files $$total_files $$total_errors $$error_files; \
		else \
			printf "%-28s ${C_GREEN}[OK]${RESET_ALL} (%d of %d files checked. %d errors found in %d files)\n" $$dir $$total_files $$total_files 0 0; \
		fi; \
		echo >> ${NORM_LOGS}; \
	done

compile_with_progress:
	@mkdir -p ${LOGS_DIR}
	@truncate -s 0 ${LOGS_DIR}/compile.log
	@LIBFT_FILES=$$(find includes/libft -name "*.c" 2>/dev/null | wc -l); \
	SRC_FILES=$$(find src -name "*.c" 2>/dev/null | wc -l); \
	TOTAL_FILES=$$((LIBFT_FILES + SRC_FILES)); \
	BAR_SIZE=50; \
	\
	if [ "$$LIBFT_FILES" -gt 0 ]; then \
		echo "Compiling libft..."; \
		counter=0; \
		for file in $$(find includes/libft -name "*.c" 2>/dev/null); do \
			counter=$$((counter + 1)); \
			percent=$$((counter * 100 / LIBFT_FILES)); \
			bar_fill=$$((counter * BAR_SIZE / LIBFT_FILES)); \
			printf "\r["; \
			for i in $$(seq 1 $$bar_fill); do printf "#"; done; \
			for i in $$(seq 1 $$((BAR_SIZE - bar_fill))); do printf " "; done; \
			printf "] %3d%%" $$percent; \
			${CC} ${CFLAGS} -c $$file -o $${file%.c}.o >> ${LOGS_DIR}/compile.log 2>&1 || touch ${LOGS_DIR}/compile_error; \
			if [ -f ${LOGS_DIR}/compile_error ]; then \
				printf "\r["; \
				for i in $$(seq 1 $$BAR_SIZE); do printf "#"; done; \
				printf "] 100%% ${C_RED}[KO]${RESET_ALL}\n"; \
				echo "Error compiling $$file"; \
				echo "Error details saved to ${LOGS_DIR}/compile.log"; \
				rm -f ${LOGS_DIR}/compile_error; \
				exit 1; \
			fi; \
		done; \
		$(MAKE) -C includes/libft >> ${LOGS_DIR}/compile.log 2>&1 || touch ${LOGS_DIR}/compile_error; \
		if [ -f ${LOGS_DIR}/compile_error ]; then \
			printf "\r["; \
			for i in $$(seq 1 $$BAR_SIZE); do printf "#"; done; \
			printf "] 100%% ${C_RED}[KO]${RESET_ALL}\n"; \
			echo "Error details saved to ${LOGS_DIR}/compile.log"; \
			rm -f ${LOGS_DIR}/compile_error; \
			exit 1; \
		else \
			printf "\r["; \
			for i in $$(seq 1 $$BAR_SIZE); do printf "#"; done; \
			printf "] 100%% ${C_GREEN}[OK]${RESET_ALL}\n"; \
		fi; \
	else \
		printf "\t%-28s ${C_YELLOW}[SKIPPED]${RESET_ALL} (no source files)\n" "libft"; \
	fi; \
	\
	if [ "$$SRC_FILES" -gt 0 ]; then \
		echo "Compiling src..."; \
		counter=0; \
		for file in $$(find src -name "*.c" 2>/dev/null); do \
			counter=$$((counter + 1)); \
			percent=$$((counter * 100 / SRC_FILES)); \
			bar_fill=$$((counter * BAR_SIZE / SRC_FILES)); \
			printf "\r["; \
			for i in $$(seq 1 $$bar_fill); do printf "#"; done; \
			for i in $$(seq 1 $$((BAR_SIZE - bar_fill))); do printf " "; done; \
			printf "] %3d%%" $$percent; \
			${CC} ${CFLAGS} ${INCLUDES} -c $$file -o $${file%.c}.o >> ${LOGS_DIR}/compile.log 2>&1 || touch ${LOGS_DIR}/compile_error; \
			if [ -f ${LOGS_DIR}/compile_error ]; then \
				printf "\r["; \
				for i in $$(seq 1 $$BAR_SIZE); do printf "#"; done; \
				printf "] 100%% ${C_RED}[KO]${RESET_ALL}\n"; \
				echo "Error compiling $$file"; \
				echo "Error details saved to ${LOGS_DIR}/compile.log"; \
				rm -f ${LOGS_DIR}/compile_error; \
				exit 1; \
			fi; \
		done; \
		$(MAKE) -C $(shell pwd) $(NAME) >> ${LOGS_DIR}/compile.log 2>&1 || touch ${LOGS_DIR}/compile_error; \
		if [ -f ${LOGS_DIR}/compile_error ]; then \
			printf "\r["; \
			for i in $$(seq 1 $$BAR_SIZE); do printf "#"; done; \
			printf "] 100%% ${C_RED}[KO]${RESET_ALL}\n"; \
			echo "Error details saved to ${LOGS_DIR}/compile.log"; \
			rm -f ${LOGS_DIR}/compile_error; \
			exit 1; \
		else \
			printf "\r["; \
			for i in $$(seq 1 $$BAR_SIZE); do printf "#"; done; \
			printf "] 100%% ${C_GREEN}[OK]${RESET_ALL}\n"; \
		fi; \
	else \
		printf "\t%-28s ${C_YELLOW}[SKIPPED]${RESET_ALL} (no source files)\n" "src"; \
	fi;

run:
	@echo "Cleaning old files..."
	@${MAKE} -s fclean
	@echo "Running norminette checks..."
	@${MAKE} -s norm
	@echo "Compiling project..."
	@${MAKE} -s compile_with_progress || exit 0
	@if [ ! -f ${BIN_DIR}/${NAME} ]; then \
		printf "%-8s ${C_RED}[FAILED]${RESET_ALL}\n" "Build"; \
		${MAKE} -s fclean; \
		exit 0; \
	else \
		printf "%-8s ${C_GREEN}[COMPLETED]${RESET_ALL}\n" "Build"; \
		${MAKE} -s clean; \
		echo "Runing with Valgrind..."; \
		${VALGRIND} ${VALGRIND_LOGS} ${BIN_DIR}/${NAME}; \
		${MAKE} -s print_valgrind_results; \
	fi

print_valgrind_results:
	@echo
	@LOG=${VGRIND_LOGFILE}; \
	ERROR="$$(grep --text 'ERROR SUMMARY:' $${LOG} | sed -nE 's/.* ([0-9,]+) errors from ([0-9,]+) contexts.*/\1 \2/p')" ; \
	SUPPRESSED_ERRORS="$$(grep --text 'ERROR SUMMARY:' $${LOG} -A 1 | grep --text 'suppressed:' | sed -nE 's/.* ([0-9,]+) from ([0-9,]+).*/\1 \2/p')" ; \
	SUPPRESSED_LEAKS="$$(if grep --text 'LEAK SUMMARY:' $${LOG} -A 5 | grep --text 'suppressed:' > /dev/null; then grep --text 'LEAK SUMMARY:' $${LOG} -A 5 | grep --text 'suppressed:' | sed -nE 's/.* ([0-9,]+) bytes in ([0-9,]+) blocks.*/\1 \2/p'; else echo '0 0'; fi)" ; \
	LEAK_DEF="$$(if grep --text 'definitely lost:' $${LOG} > /dev/null; then grep --text 'definitely lost:' $${LOG} | sed -nE 's/.* ([0-9,]+) bytes in ([0-9,]+) blocks.*/\1 \2/p'; else echo '0 0'; fi)" ; \
	LEAK_IND="$$(if grep --text 'indirectly lost:' $${LOG} > /dev/null; then grep --text 'indirectly lost:' $${LOG} | sed -nE 's/.* ([0-9,]+) bytes in ([0-9,]+) blocks.*/\1 \2/p'; else echo '0 0'; fi)" ; \
	LEAK_POS="$$(if grep --text 'possibly lost:' $${LOG} > /dev/null; then grep --text 'possibly lost:' $${LOG} | sed -nE 's/.* ([0-9,]+) bytes in ([0-9,]+) blocks.*/\1 \2/p'; else echo '0 0'; fi)" ; \
	LEAK_REA="$$(if grep --text 'still reachable:' $${LOG} > /dev/null; then grep --text 'still reachable:' $${LOG} | sed -nE 's/.* ([0-9,]+) bytes in ([0-9,]+) blocks.*/\1 \2/p'; else echo '0 0'; fi)" ; \
	if [ "$$(echo $$ERROR | awk '{print $$1}')" != "0" ]; then \
		printf "${C_RED}WARNING: Valgrind - %s errors in %s contexts!${RESET_ALL}\n" $$ERROR; \
	else \
		printf "${C_GREEN}NO ERRORS${RESET_ALL}\n"; \
	fi; \
	if [ "$$(echo $$SUPPRESSED_ERRORS | awk '{print $$1}')" != "0" ]; then \
		printf "${C_YELLOW}WARNING: Valgrind - %s suppressed errors in %s contexts.${RESET_ALL}\n" $$SUPPRESSED_ERRORS; \
	fi; \
	if [ "$$(echo $$LEAK_DEF | awk '{print $$1}')" != "0" ]; then \
		printf "${C_RED}WARNING: Valgrind - %s bytes definitely lost in %s blocks!${RESET_ALL}\n" $$LEAK_DEF; \
	else \
		printf "${C_GREEN}NO DEFINITE LEAKS${RESET_ALL}\n"; \
	fi; \
	if [ "$$(echo $$LEAK_IND | awk '{print $$1}')" != "0" ]; then \
		printf "${C_RED}WARNING: Valgrind - %s bytes indirectly lost in %s blocks!${RESET_ALL}\n" $$LEAK_IND; \
	else \
		printf "${C_GREEN}NO INDIRECT LEAKS${RESET_ALL}\n"; \
	fi; \
	if [ "$$(echo $$LEAK_POS | awk '{print $$1}')" != "0" ]; then \
		printf "${C_YELLOW}WARNING: Valgrind - %s bytes possibly lost in %s blocks!${RESET_ALL}\n" $$LEAK_POS; \
	else \
		printf "${C_GREEN}NO POSSIBLE LEAKS${RESET_ALL}\n"; \
	fi; \
	if [ "$$(echo $$LEAK_REA | awk '{print $$1}')" != "0" ]; then \
		printf "${C_YELLOW}WARNING: Valgrind - %s bytes in %s blocks still reachable!${RESET_ALL}\n" $$LEAK_REA; \
	else \
		printf "${C_GREEN}NO REACHABLE LEAKS${RESET_ALL}\n"; \
	fi; \
	if [ "$$(echo $$SUPPRESSED_LEAKS | awk '{print $$1}')" != "0" ]; then \
		printf "${C_YELLOW}WARNING: Valgrind - %s bytes in %s blocks suppressed!${RESET_ALL}\n" $$SUPPRESSED_LEAKS; \
	fi;