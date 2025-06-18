// BIBLIOTECAS
#include <gtk/gtk.h>
#include "structs.h"
#include "mainWindow.h"
#include "cliente.h"
#include "medico.h"
#include "consulta.h"

// MAIN 
int main(int argc, char **argv){
  GtkApplication *app;
    
  ST_CLIENTE clientes[MAX_CLIENTES] = {0};
  ST_MEDICO medicos[MAX_MEDICOS] = {0};
  ST_CONSULTA consultas[MAX_CONSULTAS] = {0};
    
  carregarFicheiroCliente(clientes);
  carregarFicheiroMedico(medicos);
  carregarFicheiroConsulta(consultas, clientes, medicos);

  ST_APPLICATION application = {
    .clients = clientes,
    .doctors = medicos,
    .appointments = consultas
  }; 
    
  app = gtk_application_new("clinica.gestao", G_APPLICATION_DEFAULT_FLAGS);
  g_signal_connect(app, "activate", G_CALLBACK(createMainWindow), &application);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);
    
  return status;
}
