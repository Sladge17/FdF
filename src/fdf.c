/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthuy <jthuy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/16 12:36:23 by jthuy             #+#    #+#             */
/*   Updated: 2020/03/16 19:23:45 by jthuy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		main(int argv, char **argc)
{
	t_setting	setting;

	if (argv != 2)
	{
		write(1, "Needed only one input file.\n", 28);
		exit (0);
	}
	set_model(argc[1], &setting.model, &setting.coords);
	shift_to_origin(&setting.model);


	// set_params(&setting.model);
	// // set_model(&setting.model);
	// set_overall(&setting.model);
	// set_diagonal(&setting.model);
	// shift_to_origin(&setting.model);

	// set_maxcoord(&setting.model);

	set_system(&setting.system);

	// transform_model(&setting.system, &setting.model, &setting.coords);

	drawing(&setting.system, &setting.model);

	
	
	mlx_put_image_to_window(setting.system.mlx, setting.system.win, setting.system.img, 0, 0);
	// mlx_string_put(setting.system.mlx, setting.system.win, 30, 30, 0xff, "ROTATION:");

	// mlx_hook(setting.system.win, 2, 0, key_press, &setting);
	// mlx_hook(setting.system.win, 4, 0, mouse_press, &setting);
	// mlx_hook(setting.system.win, 5, 0, mouse_release, &setting);
	// mlx_hook(setting.system.win, 6, 0, mouse_move, &setting);
	// mlx_hook(setting.system.win, 17, 0, close_fdf, &setting);

	mlx_loop (setting.system.mlx);
	
	return (0);
}

void	set_model(char *filename, t_model *model, t_coords *coords)
{
	parse(filename, model);
	model->area = model->width * model->height;
	model->rot[0] = ROT_X;
	model->rot[1] = ROT_Y;
	model->rot[2] = ROT_Z;
	set_overall(model);
	// model->overall = 0;
	set_scalepos(model, coords);
}

void	set_overall(t_model *model)
{
	int		i;

	if (!(model->o_vertex = (int **)malloc(sizeof(int *) * model->area)))
		exit(0);
	i = 0;
	while (i < model->area)
	{
		if (!(model->o_vertex[i] = (int *)malloc(sizeof(int) * 2)))
			exit(0);
		i += 1;
	}
}


void	shift_to_origin(t_model *model)
{
	int		i;

	i = 0;
	while (i < model->area)
	{
		model->vertex[i][0] -= model->vertex[model->area - 1][0] / 2;
		model->vertex[i][1] -= model->vertex[model->area - 1][1] / 2;
		i += 1;
	}
}

void	set_system(t_system *system)
{
	system->mlx = mlx_init();
	system->win = mlx_new_window(system->mlx, WIDTH, HEIGHT, "FdF");
	system->img = mlx_new_image(system->mlx, WIDTH, HEIGHT);
	system->output = (int *)mlx_get_data_addr(system->img, &system->img_s[0], &system->img_s[1], &system->img_s[2]);
	system->field = WIDTH * HEIGHT;
	set_buffers(system);
	set_backbuf(system->back_buf);
	// system->render = 2;
	// system->control = 0;
}

void	set_buffers(t_system *system)
{
	if (!(system->back_buf = (int *)malloc(sizeof(int) * system->field)))
		exit (0);
	
	// system->z_buf = (int *)malloc(sizeof(int) * system->field);
	// if (!(system->z_buf))
	// 	exit (0);
	// system->light_buf = (int *)malloc(sizeof(int) * area);
	// if (!(system->light_buf))
	// 	exit (0);
}


void	drawing(t_system *system, t_model *model)
{
	int		i;

	i = 0;
	while (i < system->field)
	{
		system->output[i] = system->back_buf[i];
		i += 1;
	}
	
	i = 0;
	while (i < model->area)
	{
		system->output[model->vertex[i][0] + model->vertex[i][1] * WIDTH] = model->vertex[i][2];
		i += 1;
	}
	
}
