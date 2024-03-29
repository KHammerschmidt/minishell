/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mio <mio@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 20:18:10 by khammers          #+#    #+#             */
/*   Updated: 2022/03/15 21:38:28 by mio              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* **************************************************************** */
/*							INCLUDES								*/
/* **************************************************************** */

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <limits.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

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
	int				flag;
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
	int				flag;
	struct s_cmd	*next;
	struct s_cmd	*previous;
}	t_cmd;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_quotes
{
	int		i;
	int		quote_on;
	int		quote_type;
	int		quote_2;
	char	*line;
}	t_quotes;

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
	int		flag;
	int		exit_status;
}	t_vars;

/* **************************************************************** */
/*							PROTOYPES								*/
/* **************************************************************** */

/* start */
int		main(int argc, char **argv, char **envp);
int		read_line(t_vars *ms);

/* environment variables */
int		init_env(t_vars *ms, char **envp);
void	free_t_env(t_env **env);
t_env	*ft_lstnew_env(char *content);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **lst, t_env *new);
void	ft_free_lst_env(t_env **lst);
t_env	*get_env_var(t_vars *ms, char *var_name);
void	update_envp_array(t_vars *ms);

/* builtins */
int		init_builtin(t_vars *ms);
int		builtin_cd(t_vars *ms, t_cmd *current);
int		builtin_echo(t_vars *ms, t_cmd *current);
int		builtin_env(t_vars *ms);
int		builtin_exit(t_vars *ms, t_cmd *current);
int		builtin_export(t_vars *ms, t_cmd *current);
void	declare_x(t_vars *ms);
int		builtin_pwd(t_vars *ms);
int		builtin_unset(t_vars *ms, t_cmd *current);
int		is_builtin(t_vars *ms, char *cmd);
void	create_old_pwd(t_vars *ms, int flag, char *start_wd);
int		export_aux(char *command, int *i);

/* cmd utils */
t_cmd	*ft_lstnew_cmd(t_vars *ms);
t_cmd	*ft_lstlast_cmd(t_cmd *lst);
void	ft_lstadd_back_cmd(t_cmd **cmd, t_cmd *element);
void	reset_info_struct(t_vars *ms);;
void	pass_on_infos_node(t_vars *ms, t_cmd *node);

/* prompt */
char	*get_user(t_vars *ms);
char	*get_pwd(t_vars *ms);
char	*create_prompt(t_vars *ms);

/* signal handling */
void	signal_handler(int signum);
void	rl_init(int i);
void	rl_reset(void);

/* lexer and parser, command table development */
int		create_cmd_table(t_vars *ms);
int		ft_syntax_check(char *str, t_vars *ms);
void	dollar_expansion(t_vars *ms);
char	*lexer_parser(t_vars *ms);
int		lexer_parser_redirections(char **string, t_vars *ms);
int		valid_pipe(char *str);
char	*parser_lexer_pipe(t_vars *ms, int quotes, char *crr, char *nxt);

/* $-sign */
void	handle_dsign(t_quotes *qt, char *str);
char	*hdoc_dollar_expansion(t_vars *ms, char *line, int dollar_flag);
int		prepare_hdoc_expansion(t_vars *ms, int *dollar_flag, char **limiter);
void	no_envar_found(t_vars *ms, char *var);
int		valid_dollar_sign(t_vars *ms, int i, int *quote_on, int quote_type);
char	*cut_unused_envar(char *str);

/* quotes */
int		quote_status(char *str);
char	**ft_split_quotes(char *str);
int		ft_count_chars(char *str, t_vars *ms);
int		check_open_closed_quote(char *str, int stop,
			int *within_quotes, int quote);
void	handle_dquotes(char *str, int *i, int quote_type, char **line);
void	handle_squotes(char *str, int *i, int quote_2, char **line);
int		closed_single_quote_in_double_quote(char *str, int i);
char	*cut_quotes(char *str);
void	set_quote_index_1(char *str, int *i, int *quote_type, int *quote_on);

/* str handling quoting */
int		compare_str(char *s1, char *s2);
int		ft_strchr_pos(char *s, char c);
char	*ft_strjoin_2(char *line, char *str, int i);
int		ft_count_substrings(char *str);
char	**copy_strarray(char **strarray);

/* redirections */
int		input_redirection(t_vars *ms, char **string, int red_in);
int		output_redirection(t_vars *ms, char **string, int red_out);
int		ft_here_doc(t_vars *ms);
int		valid_red(char *str, int pos);
int		ft_strchr_pos_red(char *s, char c, int i);

/* command execution */
int		get_paths(t_vars *ms);
int		execution_process_loop(t_vars *ms);
void	ft_processes(t_vars *ms, t_cmd *current, pid_t *pid);
int		ft_builtin_parent(t_cmd *current, t_vars *ms);
void	if_fail(t_vars *ms, t_cmd *current, char **tmp);
void	create_tmp(t_vars *ms, t_cmd *current, char **tmp);
int		if_paths(t_vars *ms, t_cmd *current, char **tmp, int *i);
int		check_if_dir(t_cmd *current);
void	execute_builtin(t_vars *ms, t_cmd *current);
void	execute_cmd(t_vars *ms, t_cmd *current);

/* free and exit */
void	last_free(t_vars *ms, int e_code);
void	free_t_env(t_env **env);
void	free_builtin_list(t_vars *ms);
void	ft_free_lst(t_list **lst);
void	ft_free_string(char **str);

/* Resetting after every input line */
void	reset(t_vars *ms);
void	free_cmd_struct(t_vars *ms);

#endif