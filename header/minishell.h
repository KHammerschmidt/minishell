#ifndef MINISHELL_H
# define MINISHELL_H

/* **************************************************************** */
/*							INCLUDES								*/
/* **************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
// # include <curses.h>
// # include <term.h>
#include <string.h>
# include <termios.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"
# include <fcntl.h>

# define BUFFER_SIZE 1


/* **************************************************************** */
/*							STRUCTS									*/
/* **************************************************************** */

typedef struct s_info
{
	char			**command;
	char			*infile;
	char			*outfile;
	int				input_op;
	int				output_op;
	int				pipe;
	int				fd_in;
	int				fd_out;
}	t_info;

typedef struct s_cmd
{
	char			**command;
	char			*execpath;
	int				fd_in;
	int				fd_out;
	char			*infile;
	char			*outfile;
	int				input_op;
	int				output_op;
	int				error_flag;
	char			*error_msg;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_vars
{
	t_env	*env;
	t_list	*builtins;
	t_cmd	*cmd;
	t_info	info;
	char	*cmd_line;
	char	*line;
	int		pipe_fd[2];
	int		tmp_fd;
	char	**paths;
	char	**envp;
	int		exit_status;
}	t_vars;

/* **************************************************************** */
/*							PROTOYPES								*/
/* **************************************************************** */

int		main(int argc, char **argv, char **envp);
int		read_line(t_vars *ms);

/* envp */
int		init_env(t_vars *ms, char **envp);
void	free_t_env(t_env **env);
t_env	*ft_lstnew_env(char *content);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_free_lst_env(t_env **lst);
t_env	*get_env_var(t_vars *ms, char *var_name);
void	update_envp_array(t_vars *ms);

/* Builtins */
int	init_builtin(t_vars *ms);
int		builtin_cd(t_vars *ms, t_cmd *current);
int		builtin_echo(t_vars *ms, t_cmd *current);
int		builtin_env(t_vars *ms, t_cmd *current);
int		builtin_exit(t_vars *ms, t_cmd *current);
int		builtin_export(t_vars *ms, t_cmd *current);
int		builtin_pwd(t_vars *ms, t_cmd *current);
int		builtin_unset(t_vars *ms, t_cmd *current);


void	execute_builtin(t_vars *ms, t_cmd *current);
void	execute_cmd(t_vars *ms, t_cmd *current);
int		is_builtin(t_vars *ms, char *cmd);

/* prompt */
char	*get_user(t_vars *ms);
char	*get_pwd(t_vars *ms);
char	*create_prompt(t_vars *ms);

/* readline init */
void	rl_init(void);
void	rl_reset(void);

/* signal handling */
void	signal_handler(int signum);

/* input parsing, command table development */
void	create_cmd_table(t_vars *ms);
void	dollar_expansion(t_vars *ms);
void	handle_redirections(char **string, t_vars *ms);
char	*handle_pipe(t_vars *ms, int quotes, char *new_cmd_line, char *command_line);
int		pipe_validity(char *str);
int		check_quote_status(char *str);
char	**ft_split_quotes(char *str);
// int		ft_strchr_pos(const char *s, int c);
int	ft_strchr_pos(const char *s, char c);
int		ft_count_chars(char *str, t_vars *ms);

/* command execution */
int		get_paths(t_vars *ms);
int		check_cmd(t_vars *ms, t_cmd *current);

/* cmd utils */
t_cmd	*ft_lstnew_cmd(t_info *info);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **cmd, t_cmd *element);
int 	ft_lstsize_cmd(t_cmd *lst);
char 	*ft_strjoin_2(char *line, char *str, int i);
int		ft_count_substrings(char *str);
void	pass_on_infos_node(t_info *info, t_cmd *node);
char	**copy_strarray(char **strarray);

/* Free and exit */
void	free_and_exit(t_vars *ms, int e_flag, int e_code);
void	ft_free_string(char **str);
void	reset_info_struct(t_info *info);

/* Printing utils */
void	print_lst(t_vars *ms);
void	print_arr(char **arr);
void	print_lst_last(t_vars *ms);

/* utils */
void	ft_free_lst(t_list **lst);
void	ft_free_lst_env(t_env **lst);
void	ft_free_arr(char **arr);
int		compare_str(char *s1, char *s2);
void	free_cmd_struct(t_vars *ms);

/* Redirections */
void	handle_redirections(char **string, t_vars *ms);
void	input_redirection(t_vars *ms, char **string, int red_in);
void	output_redirection(t_vars *ms, char **string, int red_out);
int		ft_here_doc(t_vars *ms, char *limiter);

/* Processes */
int		pipex(t_vars *ms);
void	ft_builtin_parent(t_cmd *current, t_vars *ms);



void	free_builtin_list(t_vars *ms);
#endif