#ifndef MINISHELL_H
# define MINISHELL_H

/* **************************************************************** */
/*							INCLUDES								*/
/* **************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

// #define PIPE			0
// // #define	AMPERCENT		1
// // #define SEMICOLON		2
// #define	LESS			3
// #define	GREATER			4
// #define	OPEN_BRACKET	5
// #define	CLOSING_BRACKET	6
// #define	DOLLAR			7
// #define	APOSTROPHE		8
// #define BACKSLASH		9
// #define	DOUBLE_QUOTES	10
// #define	SINGLE_QUOTES	11i
// #define	SPACE			12
// #define	TAB				13
// #define NEWLINE			14
// #define	LESSLESS		15
// #define	GREATERGREATER	16

/* **************************************************************** */
/*							STRUCTS									*/
/* **************************************************************** */

typedef struct s_info
{
	char			**command;
	char			*outfile;
	char			*infile;
	char			*errfile;
	int				op;
	int				pipe;
	int				single_quote_counter;
	int				double_quote_counter;
	int				open_quotes;
	int				dollar;
}	t_info;

typedef struct s_cmd
{
	char			**command;
	// char			*execpath;				//we need the execpath of the command if its a command
	char			*outfile;
	// int				fd_out;
	// int				fd_in;
	char			*infile;
	char			*errfile;
	int				op;
	int				pipe;					//pipe_in && pipe_out
	int				fd_out;
	struct s_cmd	*next;
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
	t_info	*info;
	char	*cmd_line;
	// char	*cwd;
	// char	*new_wd;
	// char	**execpath;
	// char	**arr;
	// char	**envp;
	// int		exit_status;
}	t_vars;

/* **************************************************************** */
/*							PROTOYPES								*/
/* **************************************************************** */

int		main(int argc, char **argv, char **envp);
int		init_struct(t_vars *ms, char **envp);
int		read_line(t_vars *ms);

/* envp */
int		init_env(t_vars *ms, char **envp);	//arr + lst
t_env	*get_env_var(t_vars *ms, char *var_name);
t_env	*ft_lstnew_env(char *content);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstlast_env(t_env *lst);

/* builtins */
void	init_builtin(t_vars *ms);				//arr + lst
void	add_builtin(t_vars *ms, char *builtin);
int		builtin_cd(t_vars *ms);
int		builtin_echo(t_vars *ms);
void	builtin_env(t_vars *ms);
int		builtin_exit(t_vars *ms);
int		builtin_export(t_vars *ms);
void	builtin_pwd(t_vars *ms);
int		builtin_unset(t_vars *ms);
int		execute_cmd(t_vars *ms);
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
int		create_cmd_table(t_vars *ms);
char	*handle_input(t_vars *ms);
int		check_quote_status(char *str);


int		check_pipes_in_quote(t_vars *ms);
char	**ft_split_quotes(char *str);
void	reset_info_struct(t_info *info);
int		quote_infos(t_vars *ms, char *str);
int		check_pipe_validity(char *str);
int		ft_strchr_pos(const char *s, int c);
char	*cut_quotes(char *str);
int		ft_count_substrings(char *str);
int		ft_count_chars(char *str, t_vars *ms);
char	*dollar_expansion(t_vars *ms);

t_cmd	*init_cmd_lst(t_vars *ms, int size);
void	reset_info_struct(t_info *info);
void	pass_on_infos_node(t_info *info, t_cmd *node);

/* cmd utils */
t_cmd	*ft_lstnew_cmd(t_info *info);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **cmd, t_cmd *element);
char 	*ft_strjoin_2(char *line, char *str, int i);
int		ft_count_substrings(char *str);
void	pass_on_infos_node(t_info *info, t_cmd *node);

/* Free and exit */
void	free_and_exit(t_vars *ms, int e_flag, int e_code);
void	ft_free_string(char *str);

/* Printing utils */
void	print_lst(t_vars *ms);
void	print_arr(char **arr);

/* utils */
void	ft_free_lst(t_list **lst);
void	ft_free_lst_env(t_env **lst);
void	ft_free_arr(char **arr);
int		compare_str(char *s1, char *s2);
void	free_cmd_struct(t_vars *ms);

/* Redirections */
void 	ft_cut_infile_redirections(char **string, t_vars *ms);
void 	ft_cut_outfile_redirections(char **string, t_vars *ms);
void 	infile_redirection(char **string, t_vars *ms);
void 	outfile_redirection(char **string, t_vars *ms);
void	check_redirections(char **string, int pipe_marker, t_vars *ms);
void	check_redirections(char **string, int pipe_marker, t_vars *ms);

// void	ft_get_exec_path(t_vars *ms);
// t_cmd	*init_cmd_lst(t_vars *ms, int size);
// void	reset_info_struct(t_info *info);

#endif