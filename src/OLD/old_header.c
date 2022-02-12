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

typedef struct s_input
{
	// int	quoting;
	// int	special_char;
	// int	pipe;
	// int	less;
	// int	greater;
	// int	dollar;

	// int	space;
	// int	newline;
	// int lessless;
	// int	greatergreater;
	// int	bracket_counter_open;
	// int	bracket_counter_closed;
	// int	bracket_counter;
	// int	valid;
}	t_input;
