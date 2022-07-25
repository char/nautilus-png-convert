#include "nautilus-png-convert.h"
#include "nautilus-png-convert-config.h"

#include <glib.h>
#include <nautilus-extension.h>

void nautilus_module_initialize(GTypeModule *module) {
  nautilus_png_convert_register_type(module);
}

void nautilus_module_shutdown(void) {
}

void nautilus_module_list_types(const GType **types, int *num_types) {
  static GType provider_type_list[1];
  provider_type_list[0] = NAUTILUS_PNG_CONVERT_TYPE;

  *types = provider_type_list;
  *num_types = G_N_ELEMENTS(provider_type_list);
}
