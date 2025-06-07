// BIBLIOTECAS
#include <gtk/gtk.h>
#include "structs.h"
#include "mainWindow.h"

// MAIN 
int main(int argc, char **argv){
  GtkApplication *app;
    
  ST_CLIENTE clientes[MAX_CLIENTES];
  ST_MEDICO medicos[MAX_MEDICOS];
  ST_CONSULTA consultas[MAX_CONSULTAS];
    
  carregarFicheiroCliente(clientes);
  carregarFicheiroMedico(medicos);
  carregarFicheiroConsulta(consultas, clientes, medicos);
    
  app = gtk_application_new("clinica.gestao", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(createMainWindow), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
    
  return status;
}
