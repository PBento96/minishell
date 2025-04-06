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

run:
	@${MAKE} -s re
	@${MAKE} -s fclean
	${VALGRIND} ${VALGRIND_LOGS} ${BIN_DIR}/${NAME}
	@${MAKE} -s print_valgrind_results

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