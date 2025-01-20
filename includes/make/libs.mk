##	HELPER FILES
include	./includes/make/vars.mk

##	INITIALIZE FOLDERS
init:
	@if [ ! -d "${BIN_DIR}" ]; then \
		mkdir -p bin; \
	fi
	@if [ ! -d "${LOGS_DIR}" ]; then \
		mkdir -p logs; \
	fi

##	LIBFT FUNCTIONS
libft: libft_clone
	${MAKE} -C ${LIBFT_DIR}

libft_clone:
	@if [ ! -d "${LIBFT_DIR}" ]; then \
		git clone "${LIBFT_REPO}" "${LIBFT_DIR}"; \
	fi
	@rm -rf "${LIBFT_DIR}/.git"

libft_clean:
	@if [ -d "${LIBFT_DIR}" ]; then \
		${MAKE} clean -C ${LIBFT_DIR}; \
	fi

libft_fclean:
	@if [ -d "${LIBFT_DIR}" ]; then \
		${MAKE} fclean -C ${LIBFT_DIR}; \
	fi

libft_re:
	@rm -rf ${LIBFT_DIR}
	@${MAKE} --no-print-directory -s get_libft