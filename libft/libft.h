/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:48:58 by ccormon           #+#    #+#             */
/*   Updated: 2024/03/07 11:04:19 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include <stddef.h>
# include <stdbool.h>
# include <limits.h>
# include <stdarg.h>
# include <fcntl.h>

# define BUFFER_SIZE 5

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// ft_alloc
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

// ft_is
bool	ft_isalpha(int c);
bool	ft_isdigit(int c);
bool	ft_isalnum(int c);
bool	ft_isascii(int c);
bool	ft_isprint(int c);

// ft_lst
t_list	*ft_lstnew(void *content);
void	ft_lstadd_front(t_list **alst, t_list *new);
size_t	ft_lstsize(t_list *lst);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void*));

// ft_mem
void	*ft_memset(void *s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memchr(const void *s, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);

// ft_printf
int		ft_printf(const char *format, ...);
int		ft_choice(const char *format, size_t i, va_list arg_list);
int		ft_printfchar(int c);
int		ft_printfhex(unsigned long long n, char *basehex);
int		ft_printfnbr(int n);
int		ft_printfpointer(unsigned long long n, char *basehex);
int		ft_printfstr(char *s);
int		ft_printfunbr(unsigned int n);
void	ft_putchar(int c);
void	ft_puthex(unsigned long long n, char *basehex);
void	ft_putnbr(unsigned int n);
void	ft_putstr(char *str);

// ft_put_fd
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

// ft_str
size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
int		ft_toupper(int c);
int		ft_tolower(int c);
char	*ft_strchr(const char *s, int c);
char	*ft_strrchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *big, const char *little, size_t len);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strtrim(char const *s1, char const *set);
char	**ft_split(char const *s, char c);
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void	ft_striteri(char *s, void (*f)(unsigned int, char*));
bool	ft_strcmp(const char *s1, const char *s2);

// ft_to
int		ft_atoi(const char *nptr);
char	*ft_itoa(int n);

// get_next_line
char	*get_next_line(int fd);
ssize_t	readline(ssize_t byte_read, char *buffer, char **readed, int fd);
bool	ft_isinstr(char *str, int c);
void	addtoreaded(char **readed, char *buffer);
char	*addtoline(char *readed);
void	cleanreaded(char **readed);

#endif
