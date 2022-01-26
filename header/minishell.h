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
// #define	SINGLE_QUOTES	11
// #define	SPACE			12
// #define	TAB				13
// #define NEWLINE			14
// #define	LESSLESS		15
// #define	GREATERGREATER	16

/* **************************************************************** */
/*							STRUCTS									*/
/* **************************************************************** */

// #define	LESS			3
// #define	LESSLESS		4
// #define GREATER			5
// #define GREATERGREATER	6

// typedef struct	s_command
// {
// 	int num_available_simple_cmds;
// 	int	num_simple_cmds;
// 	// simplecommand **simple_cmds;			//constructs an empty command
// 	char	*outfile;						//NULL if no redirection
// 	char	*infile;						//NULL if no redirection
// 	char	*errfile;						//NULL if no redirection
// 	// int		background;

// 	// void	prompt();
// 	// void	print();
// 	// void	execute();
// 	// void	clear();

// 	// void insertSimpleCommand( SimpleCommand * simpleCommand );
// 	// static Command _currentCommand;					//used to build the command and simple command during
// 	// static SimpleCommand *_currentSimpleCommand;	//the parsing of the command
// } t_command;

// typedef struct	s_simplecmd
// {
// 	int	num_available_args;
// 	int	num_args;
// 	char	**args;

// 	// SimpleCmd();							//constructs a cimple empty command
// 	// void	insertArgument(char *argument);	//inserts a new argument into the simplecommand & enlargens the _args if necessary,
// 											//last element must be NULL (execve call)
// } t_simplecmd;


// typedef struct s_smple_cmd_lst
// {
// 	int		num_available_args;
// 	t_cmd	*cmd;
// }	t_smple_cmd;


// typedef struct s_input
// {
// 	// int	quoting;
// 	// int	special_char;
// 	// int	pipe;
// 	// int	less;
// 	// int	greater;
// 	// int	dollar;
// 	int	single_quotes_counter;
// 	int	double_quote_counter;
// 	int	open_quotes;
// 	// int	space;
// 	// int	newline;
// 	// int lessless;
// 	// int	greatergreater;
// 	// int	bracket_counter_open;
// 	// int	bracket_counter_closed;
// 	// int	bracket_counter;
// 	// int	valid;
// }	t_input;

typedef struct s_cmd
{
	int				index;
	char			*command;
	char			*args;
	char			*outfile;				//NULL if no redirection
	char			*infile;				//NULL if no redirection
	char			*errfile;
	int				op;
	int				pipe;
	struct s_cmd	*next;
}	t_cmd;

typedef struct	s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
} 	t_env;

typedef struct s_vars
{
	t_list	*lst;
	t_env	*env;
	t_list	*builtins;
	t_cmd	*cmd;

	int		argc;
	char	**argv;
	char	*cmd_line;
	// char	**execpath;

	char	*cwd;
	char	*new_wd;
	int		fd_out;
	// t_input	*input;
	// char	**arr;
	// char	*quoting;
	// char	**envp;
	// int		exit_status;

} t_vars;

/* **************************************************************** */
/*							PROTOYPES								*/
/* **************************************************************** */

int		main(int argc, char **argv, char **envp);
int		init_struct(t_vars *ms, int argc, char **argv, char **envp);

int		parsing(t_vars *ms);
int		read_line(t_vars *ms);

// int		detect_cmds(t_vars *ms);
// int		init_cmd_list(t_vars *ms, char *cmd_line);
int		get_start(char *cmd_line);
int		get_end(char *cmd_line);

/* envp */
int		init_env(t_vars *ms, char **envp);	//arr + lst
void	ft_lstadd_back_env(t_env **lst, t_env *new);
t_env	*ft_lstlast_env(t_env *lst);
t_env	*ft_lstnew_env(char *content);
t_env	*get_env_var(t_vars *ms, char *var_name);

/* builtins */
void	init_builtin(t_vars *ms);				//arr + lst
void	add_builtin(t_vars *ms, char *builtin);
int		builtin_cd(t_vars *ms, char *dir);
void	builtin_echo(t_vars *ms, char *str, int no_nl_flag);
void	builtin_pwd(t_vars *ms);
void	builtin_env(t_vars *ms);
int		builtin_unset(t_vars *ms, char *var_name);
int		builtin_export(t_vars *ms, char *var_name, char *var_value);

/* utils */
void	ft_free_lst(t_list **lst);
void	ft_free_lst_env(t_env **lst);
void	ft_free_arr(char **arr);
int		compare_str(char *s1, char *s2);

/* prompt */
char	*get_user(t_vars *ms);
char	*get_pwd(t_vars *ms);
char	*create_prompt(t_vars *ms);

/* readline init */
void	rl_init(void);
void	rl_reset(void);

/* signal handling */
void	signal_handler(int signum);

int		create_cmd_table(t_vars *ms);

void	print_lst(t_vars *ms);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd	*ft_lstnew_cmd(void);

void	ft_free_string(char *str);
int		ft_strchr_pos(const char *s, int c);

#endif