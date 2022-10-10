/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jabae <jabae@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 12:58:55 by jabae             #+#    #+#             */
/*   Updated: 2022/10/10 12:58:56 by jabae            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "./utils.h"
# include <errno.h>
# include <string.h>
# include <unistd.h>

void	execute(t_argv *argv);
/* run_fork */
void	run_fork(t_argv *argv, pid_t *pids, int **pipes, int cnt_pipe);
/* builtin */
int		is_builtin(char **cmd);
void	run_builtin_proc(char **cmd);
void	single_builtin(t_argv *argv);
/* init_execute */
void	set_pipe_cnt(int *cnt_pipe, t_argv *argv);
void	set_pids(pid_t **pids, int cnt_pipe);
int		set_pipes(int ***pipes, int cnt_pipe);
/* open */
int		ft_open(char *file, int type);
/* path */
char	*get_path(char *cmd);
/* pipe */
void	set_stdout_pipe(t_argv *argv, int **pipes, int num);
void	set_stdin_pipe(int **pipes, int num);
void	close_pipes(int **pipes, int cnt);
void	free_pipes(int **pipes);
/* redir */
void	reset_stdin(int fd);
void	reset_stdout(int fd);
int		set_stdin_redir(t_argv *argv);
int		set_stdout_redir(t_argv *argv);
/* hdoc */
int		check_heredoc(t_argv *argv);
void	unlink_hdoc(t_argv *argv);

/* mandatory part */
void	ft_pwd(char **cmd);
void	ft_cd(char **cmd);
void	ft_env(char **cmd);
void	ft_unset(char **cmd);
void	ft_export(char **cmd);
void	ft_echo(char **cmd);
void	ft_exit(char **cmd);

#endif
