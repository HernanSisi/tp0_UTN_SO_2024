#include "client.h"

int main(void)
{
	int conexion;
	char *ip;
	char *puerto;
	char *valor;

	t_log *logger;
	t_config *config;

	logger = iniciar_logger();
	log_info(logger, "Iniciando ejecucion");
	config = iniciar_config();
	if (config == NULL)
	{
		log_info(logger, "no se leyo el archivo de configuracion");
		exit(EXIT_FAILURE);
	}
	else
	{
		log_info(logger, "se leyo correctamente el archivo de configuracion");
	}
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	valor = config_get_string_value(config, "CLAVE");
	log_info(logger, "IP config: %s", ip);
	log_info(logger, "PUERTO config: %s", puerto);
	log_info(logger, "CLAVE config: %s", valor);
	conexion = crear_conexion(ip, puerto);
	enviar_mensaje(valor, conexion);
	paquete(conexion);

	log_info(logger, "Fin de Ejecucion");

	terminar_programa(conexion, logger, config);
}

t_log *iniciar_logger(void)
{
	t_log *nuevo_logger = log_create("tp0.log", "LogTP0", true, LOG_LEVEL_INFO);
	return nuevo_logger;
}

t_config *iniciar_config(void)
{
	t_config *nuevo_config = config_create("cliente.config");

	return nuevo_config;
}

void leer_consola(t_log *logger)
{
	char *leido = readline("> ");
	if (strcmp(leido, "") == 0)
	{
		free(leido);
		return;
	}
	do
	{
		log_info(logger, "usuario -> %s", leido);
		free(leido);
		leido = readline("> ");
	} while (strcmp(leido, "") != 0);
	free(leido);
}

void paquete(int conexion)
{
	// Ahora toca lo divertido!
	t_paquete *paquete = crear_paquete();
	t_log *logger = log_create("tp0.log", "LogTP0", false, LOG_LEVEL_INFO);
	int contador = 0;
	// Leemos y esta vez agregamos las lineas al paquete
	char *leido = readline("> ");
	while (strcmp(leido, "") != 0)
	{
		agregar_a_paquete(paquete, leido, strlen(leido)+1);
		log_info(logger, "usuario -> %s", leido);
		contador++;
		free(leido);
		leido = readline("> ");
	}
	if (contador > 0)
	{
		enviar_paquete(paquete,conexion);
	}
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	log_destroy(logger);
	eliminar_paquete(paquete);
	free(leido);
}

void terminar_programa(int conexion, t_log *logger, t_config *config)
{
	/* Y por ultimo, hay que liberar lo que utilizamos (conexion, log y config)
	  con las funciones de las commons y del TP mencionadas en el enunciado */
}