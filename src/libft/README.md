<h1>libft</h1>
Este proyecto consiste en crear una librería en lenguaje C recreando varias funciones existentes de la libc y también introduciendo algunas funciones nuevas.
<h2>Mandatory</h2>
La parte obligatoria junta funciones ya existentes con algunas añadidas con las cuales se puede manipular memoria, strings, etc.
<h3>Parte 1 - Funciones de libc</h3>
<table>
  <tr>
    <th>Función</th>
    <th>Prototipo</th>
  </tr>
  <tr>
    <td>isalpha</td>
    <td><code>int ft_isalpha(int c)</code></td>
  </tr>
  <tr>
    <td>isdigit</td>
    <td><code>int ft_isdigit(int c)</code></td>
  </tr>
  <tr>
    <td>isalnum</td>
    <td><code>int ft_isalnum(int c)</code></td>
  </tr>
  <tr>
    <td>isascii</td>
    <td><code>int ft_isascii(int c)</code></td>
  </tr>
  <tr>
    <td>isprint</td>
    <td><code>int ft_isprint(int c)</code></td>
  </tr>
  <tr>
    <td>strlen</td>
    <td><code>size_t ft_strlen(const char *s)</code></td>
  </tr>
  <tr>
    <td>memset</td>
    <td><code>void *ft_memset(void *s, int c, size_t n)</code></td>
  </tr>
  <tr>
    <td>bzero</td>
    <td><code>void ft_bzero(void *s, size_t n)</code></td>
  </tr>
  <tr>
    <td>memcpy</td>
    <td><code>void *ft_memcpy(void *dest, const void *src, size_t n)</code></td>
  </tr>
  <tr>
    <td>memmove</td>
    <td><code>void *ft_memmove(void *dest, const void *src, size_t n)</code></td>
  </tr>
  <tr>
    <td>strlcpy</td>
    <td><code>size_t ft_strlcpy(char *dst, const char *src, size_t size)</code></td>
  </tr>
  <tr>
    <td>strlcat</td>
    <td><code>size_t ft_strlcat(char *dst, const char *src, size_t size)</code></td>
  </tr>
  <tr>
    <td>toupper</td>
    <td><code>int ft_toupper(int c)</code></td>
  </tr>
  <tr>
    <td>tolower</td>
    <td><code>int ft_tolower(int c)</code></td>
  </tr>
  <tr>
    <td>strchr</td>
    <td><code>char *ft_strchr(const char *s, int c)</code></td>
  </tr>
  <tr>
    <td>strrchr</td>
    <td><code>char *ft_strrchr(const char *s, int c)</code></td>
  </tr>
  <tr>
    <td>strncmp</td>
    <td><code>int ft_strncmp(const char *s1, const char *s2, size_t n)</code></td>
  </tr>
  <tr>
    <td>memchr</td>
    <td><code>void *ft_memchr(const void *s, int c, size_t n)</code></td>
  </tr>
  <tr>
    <td>memcmp</td>
    <td><code>int ft_memcmp(const void *s1, const void *s2, size_t n)</code></td>
  </tr>

  <tr>
    <td>strnstr</td>
    <td><code>char *ft_strnstr(const char *haystack, const char *needle, size_t len)</code></td>
  </tr>
  <tr>
    <td>atoi</td>
    <td><code>int ft_atoi(const char *str)</code></td>
  </tr>
   <tr>
    <td>calloc</td>
    <td><code>void	*ft_calloc(size_t nitems, size_t size)</code></td>
  </tr>
  <tr>
    <td>strdup</td>
    <td><code>char	*ft_strdup(const char *s)</code></td>
  </tr>
</table>
<h3>Parte 2 - Funciones adicionales</h3>
<table>
  <tr>
    <th>Función</th>
    <th>Prototipo</th>
  </tr>
  <tr>
    <td>ft_substr</td>
    <td><code>char *ft_substr(char const *s, unsigned int start,
size_t len)</code></td>
  </tr>
  <tr>
    <td>ft_strjoin</td>
    <td><code>char *ft_strjoin(char const *s1, char const *s2)</code></td>
  </tr>
  <tr>
    <td>ft_strtrim</td>
    <td><code>char *ft_strtrim(char const *s1, char const *set)</code></td>
  </tr>
  <tr>
    <td>ft_split</td>
    <td><code>char **ft_split(char const *s, char c)</code></td>
  </tr>
  <tr>
    <td>ft_itoa</td>
    <td><code>char *ft_itoa(int n)</code></td>
  </tr>
  <tr>
    <td>ft_strmapi</td>
    <td><code>char *ft_strmapi(char const *s, char (*f)(unsigned
int, char))</code></td>
  </tr>
  <tr>
    <td>ft_striteri</td>
    <td><code>void ft_striteri(char *s, void (*f)(unsigned int,
char*))</code></td>
  </tr>
  <tr>
    <td>ft_putchar_fd</td>
    <td><code>void ft_putchar_fd(char c, int fd)</code></td>
  </tr>
  <tr>
    <td>ft_putstr_fd</td>
    <td><code>void ft_putstr_fd(char *s, int fd)</code></td>
  </tr>
  <tr>
    <td>ft_putendl_fd</td>
    <td><code>void ft_putendl_fd(char *s, int fd)</code></td>
  </tr>
  <tr>
    <td>ft_putnbr_fd</td>
    <td><code>void ft_putnbr_fd(int n, int fd)</code></td>
  </tr>
</table>
<h2>Bonus</h2>
La parte del bonus consiste en crear funciónes con las cuales crear y manipular listas enlazadas.
La estructura de los nodos es la siguiente:
<pre><code>typedef struct s_list
{
  void *content;
  struct s_list *next;
}              t_list;
</code></pre>
<table>
  <tr>
    <th>Función</th>
    <th>Prototipo</th>
  </tr>
  <tr>
    <td>ft_lstnew</td>
    <td><code>t_list *ft_lstnew(void *content)</code></td>
  </tr>
  <tr>
    <td>ft_lstadd_front</td>
    <td><code>void ft_lstadd_front(t_list **lst, t_list *new)</code></td>
  </tr>
  <tr>
    <td>ft_lstsize</td>
    <td><code>int ft_lstsize(t_list *lst)</code></td>
  </tr>
  <tr>
    <td>ft_lstlast</td>
    <td><code>t_list *ft_lstlast(t_list *lst)</code></td>
  </tr>
  <tr>
    <td>ft_lstadd_back</td>
    <td><code>void ft_lstadd_back(t_list **lst, t_list *new)</code></td>
  </tr>
  <tr>
    <td>ft_lstdelone</td>
    <td><code>void ft_lstdelone(t_list *lst, void (*del)(void
*))</code></td>
  </tr>
  <tr>
    <td>ft_lstclear</td>
    <td><code>void ft_lstclear(t_list **lst, void (*del)(void
*))</code></td>
  </tr>
  <tr>
    <td>ft_lstiter</td>
    <td><code>void ft_lstiter(t_list *lst, void (*f)(void *))</code></td>
  </tr>
  <tr>
    <td>ft_lstmap</td>
    <td><code>t_list *ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *))</code></td>
  </tr>
</table>
