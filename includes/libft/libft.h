/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pda-silv <pda-silv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:32:33 by pda-silv          #+#    #+#             */
/*   Updated: 2024/12/02 09:57:45 by pda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>
# include <stdint.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "ft_ansi.h"

/**
 * @brief Enum to use as return values and error codes.
 */
typedef enum e_retval
{
	OK = 0,
	NOK = -1,
	ERR_MEM = 1,
	ERR_IO = 2,
	ERR_FILE = 3,
	ERR_ARGS = 4
}	t_retval;

/** 
 * @brief Singly linked list. 
*/
typedef struct s_list
{
	void			*content;	/** Pointer to node content. */
	struct s_list	*next;		/** Pointer to next node in list. */
}	t_list;

/** 
 * @brief Doubly linked list. 
*/
typedef struct s_dlist
{
	void			*content;	/** Pointer to node content. */
	struct s_dlist	*next;		/** Pointer to next node in list. */
	struct s_dlist	*prev;		/** Pointer to previous node in list. */
}	t_dlist;

/** 
 * @brief Absolutes an integer.
 * @param n Number to absolute.
 * @returns Absolute value of n.
*/
int		ft_abs(const int n);

/** 
 * @brief Absolutes a long integer.
 * @param n Number to absolute.
 * @returns Absolute value of n.
*/
long	ft_labs(const long n);

/** 
 * @brief Converts string to integer.
 * @param str String to convert.
 * @returns String as int or 0 if invalid.
*/
int		ft_atoi(const char *str);

/** 
 * @brief Converts string to long integer.
 * @param str String to convert.
 * @returns String as long or 0 if invalid.
*/
long	ft_atol(const char *str);

/** 
 * @brief Sets memory area to zero. 
 * @param ptr Pointer to start of memory area to clear.
 * @param n Number of bytes to clear.
 * @returns Nothing.
 */
void	ft_bzero(void *ptr, size_t n);

/** 
 * @brief Allocates memory for a number of items and sets all bytes to 0. 
 * @param nitems Number of items to alocate memory for.
 * @param size Size in bytes of each item.
 * @returns Pointer to allocated memory.
*/
void	*ft_calloc(size_t nitems, size_t size);

/** 
 * @brief Checks if char is alphanumeric.
 * @param c Character to check.
 * @returns 1 if true, 0 if false.
*/
int		ft_isalnum(int c);

/** 
 * @brief Checks if char is a letter.
 * @param c Character to check.
 * @returns 1 if true, 0 if false.
*/
int		ft_isalpha(int c);

/** 
 * @brief Checks if char is ASCII.
 * @param c Character to check.
 * @returns 1 if true, 0 if false.
*/
int		ft_isascii(int c);

/** 
 * @brief Checks if char is digit.
 * @param c Character to check.
 * @returns 1 if true, 0 if false.
*/
int		ft_isdigit(int c);

/** 
 * @brief Checks if char is printable.
 * @param c Character to check.
 * @returns 1 if true, 0 if false.
*/
int		ft_isprint(int c);

/** 
 * @brief Checks if char is whitespace.
 * @param c Character to check.
 * @returns 1 if true, 0 if false.
*/
int		ft_isspace(int c);

/** 
 * @brief Checks if char is lowercase.
 * @param c Character to check.
 * @returns 1 if true, 0 if false.
*/
int		ft_islower(int c);

/** 
 * @brief Checks if char is uppercase.
 * @param c Character to check.
 * @returns 1 if true, 0 if false.
*/
int		ft_isupper(int c);

/** 
 * @brief Converts integer to string.
 * @param n Integer to conver.
 * @return Pointer to string or NULL if invalid.
 */
char	*ft_itoa(int n);

/** 
 * @brief Adds a node to the end of a linked list. 
 * @param lst Pointer to the list.
 * @param new Pointer to new node.
 * @returns Nothing.
*/
void	ft_lstadd_back(t_list **lst, t_list *new);

/** 
 * @brief Adds a node to the start of a linked list.
 * @param lst Pointer to the list.
 * @param new Pointer to new node.
 * @returns Nothing.
*/
void	ft_lstadd_front(t_list **lst, t_list *new);

/** 
 * @brief Frees all nodes in a linked list. 
 * @param lst Pointer to the list.
 * @param del Pointer to the function used to free each node's content.
 * @returns Nothing.
*/
void	ft_lstclear(t_list **lst, void (*del)(void*));

/** 
 * @brief Frees a single node in a linked list. 
 * @param lst Pointer to the node.
 * @param del Pointer to the function used to free the node's content.
 * @returns Nothing.
*/
void	ft_lstdelone(t_list *lst, void (*del)(void*));

/** 
 * @brief Iterates through a linked list and applies a function to the content.
 * @param lst Pointer to the list.
 * @param f Pointer to the function to apply.
 * @returns Nothing.
*/
void	ft_lstiter(t_list *lst, void (*f)(void *));

/** 
 * @brief Returns last node of a linked list.
 * @param lst Pointer to the linked list.
 * @returns Pointer to the last node of the list or NULL if empty.
*/
t_list	*ft_lstlast(t_list *lst);

/** 
 * @brief Creates new list resulting with the aplication of a function to a list.
 * @param lst Pointer to the linked list.
 * @param f Pointer to the function to apply.
 * @param del Pointer to function to free node in case of error.
 * @returns Pointer to a new list or NULL if error.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/** 
 * @brief Allocates new linked list node. 
 * @param content Pointer to the node's content.
 * @returns Pointer to the new node or NULL if error.
*/
t_list	*ft_lstnew(void *content);

/** 
 * @brief Calculates the size of a linked list.
 * @param lst Pointer to the linked list.
 * @returns Number of nodes in the list.
*/
int		ft_lstsize(t_list *lst);

/** 
 * @brief Scans for the first occurence of a value in a memory area.
 * @param s Pointer to the start of the memory area.
 * @param c Value to search for.
 * @param n size in bytes of the memory area.
 * @returns Pointer to the first occurence of the value or NULL if not found.
*/
void	*ft_memchr(const void *s, int c, size_t n);

/** 
 * @brief Compares two memory areas up to n bytes.
 * @param s1 Pointer to memory area to compare.
 * @param s2 Pointer to memory area to compare.
 * @param n Number of bytes to compare.
 * @returns Diference between the first unequal bytes or 0 if equal.
*/
int		ft_memcmp(const void *s1, const void *s2, size_t n);

/** @brief Copies n bytes from src to dest. */
void	*ft_memcpy(void *dest, const void *src, size_t n);

/** @brief Copies n bytes from src to dest. The memory areas may overlap. */
void	*ft_memmove(void *dest, const void *src, size_t n);

/** @brief Sets n bytes starting at s with c. */
void	*ft_memset(void *s, int c, size_t n);

/** @brief Outputs c to the given file descriptor. */
void	ft_putchar_fd(char c, int fd);

/** @brief Outputs s to the given file descriptor, followed by newline. */
void	ft_putendl_fd(char *s, int fd);

/** @brief Outputs n to the given file descriptor. */
void	ft_putnbr_fd(int n, int fd);

/** @brief Outputs s to the given file descriptor. */
void	ft_putstr_fd(char *s, int fd);

/** @brief Returns strings obtained by splitting s using c as a delimiter. */
char	**ft_split(char const *s, char c);

/** @brief Locates the first occurrence of c in s. */
char	*ft_strchr(const char *s, int c);

/** @brief Duplicates str1. */
char	*ft_strdup(const char *str1);

/** @brief Applies function f to each character of s. */
void	ft_striteri(char *s, void (*f)(unsigned int, char*));

/** @brief Returns the concatenation of s1 and s2. */
char	*ft_strjoin(char const *s1, char const *s2);

/** @brief Appends src to the end of dst. */
size_t	ft_strlcat(char *dst, const char *src, size_t size);

/** @brief Copies up to size - 1 chars from src to dst, NULL-terminating. */
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

/** @brief Computes the length of s. */
size_t	ft_strlen(const char *s);

/** @brief Applies function f to each character of s to create a new string. */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/** @brief Compares first n bytes of s1 and s2. */
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/** @brief Locates first occurrence of little in the first len chars of big. */
char	*ft_strnstr(const char *big, const char *little, size_t len);

/** @brief Locates last occurrence of c in the string s. */
char	*ft_strrchr(const char *s, int c);

/** @brief Returns a copy of s1 with the chars in set removed from the ends. */
char	*ft_strtrim(char const *s1, char const *set);

/** @brief Returns a substring from s begining at start and of max size len. */
char	*ft_substr(char const *s, unsigned int start, size_t len);

/** @brief Converts c to lowercase. */
int		ft_tolower(int c);

/** @brief Converts c to uppercase. */
int		ft_toupper(int c);

/** @brief Reads the next line from the file descriptor. */
char	*get_next_line(int fd);

/** @brief Writes formated output to stdout. */
int		ft_printf(const char *format, ...);

/** @brief Returns first node of lst. */
t_dlist	*ft_dlstfirst(t_dlist *lst);

/** @brief Returns last node of lst. */
t_dlist	*ft_dlstlast(t_dlist *lst);

/** @brief Iterates through lst and applies function f to the content. */
void	ft_dlstiter(t_dlist *lst, void (*f)(void *));

/** @brief Returns number of nodes in lst. */
int		ft_dlstsize(t_dlist *lst);

/** @brief Allocates new linked list node. */
t_dlist	*ft_dlstnew(void *content);

/** @brief Creates new list resulting with the result of function f. */
t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *));

/** @brief Frees lst using del function. */
void	ft_dlstdelone(t_dlist *lst, void (*del)(void*));

/** @brief Frees lst and all following nodes using del function. */
void	ft_dlstclear(t_dlist **lst, void (*del)(void *));

/** @brief Adds new to the start of lst. */
void	ft_dlstadd_front(t_dlist **lst, t_dlist *new);

/** @brief Adds new to the end of lst. */
void	ft_dlstadd_back(t_dlist **lst, t_dlist *new);

/** @brief Adds new between prev and next. */
void	ft_dlstadd_mid(t_dlist *prev, t_dlist *next, t_dlist *new);

/** @brief Safe version of free, resets ptr to NULL after freeing memory */
void	ft_free(void **ptr);

#endif
