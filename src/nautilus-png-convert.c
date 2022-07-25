#include "nautilus-png-convert.h"
#include "nautilus-png-convert-config.h"

#include <glib.h>
#include <nautilus-extension.h>

static GType png_convert_type = 0;
static GObjectClass *parent_class;

static void convert_file(NautilusFileInfo *file_info) {
  GFile *file = nautilus_file_info_get_location(file_info);
  gchar *file_name = g_file_get_path(file);

  gchar *base = g_strdup(file_name);
  gchar *extension = g_strdup(strrchr(base, '.'));
	if (extension != NULL)
    base[strlen(base) - strlen(extension)] = '\0';
  gchar *new_file_name = g_strdup_printf("%s.png", base);
  g_free(base);

  gchar *argv[4];
  argv[0] = "/usr/bin/magick";
  argv[1] = file_name;
  argv[2] = new_file_name;
  argv[3] = NULL;

  pid_t pid;
  if (!g_spawn_async(NULL, argv, NULL, G_SPAWN_DO_NOT_REAP_CHILD, NULL, NULL, &pid, NULL))
    return;

  g_free(file_name);
  g_free(new_file_name);
  g_object_unref(file);
}

static void image_convert_callback(NautilusMenuItem *item, GList *files) {
  for (GList *file_info = files; file_info != NULL; file_info = file_info->next) {
    convert_file(file_info->data);
  }

  nautilus_file_info_list_free(files);
}

static gboolean nautilus_png_convert_file_is_image(NautilusFileInfo *file_info) {
  gboolean maybe_image = TRUE;

  gchar *uri_scheme = nautilus_file_info_get_uri_scheme(file_info);
  if (strcmp(uri_scheme, "file") != 0)
    maybe_image = FALSE;
  g_free(uri_scheme);

  gchar *mime_type = nautilus_file_info_get_mime_type(file_info);
  if (strncmp(mime_type, "image/", 6) != 0)
    maybe_image = FALSE;
  // We also don't want to convert PNGs to PNG:
  if (strncmp(mime_type, "image/png", 9) == 0)
    maybe_image = FALSE;
  g_free(mime_type);

  return maybe_image;
}

static GList* nautilus_png_convert_get_file_items(NautilusMenuProvider *provider, GtkWidget *window, GList *files) {
  GList *items = NULL;
  NautilusMenuItem *item;

  for (GList *file = files; file != NULL; file = file->next) {
    if (!nautilus_png_convert_file_is_image(file->data))
      return NULL;
  }

  for (GList *file = files; file != NULL; file = file->next) {
    item = nautilus_menu_item_new("NautilusPNGConvert::convert", "Convert to PNG", "Convert each selected image to PNG", "camera-photo");
    g_signal_connect(item, "activate", G_CALLBACK(image_convert_callback), nautilus_file_info_list_copy(files));
    items = g_list_append(items, item);

    return items;
  }

  return NULL;
}

static GList* nautilus_png_convert_get_background_items(NautilusMenuProvider *provider, GtkWidget *window, NautilusFileInfo *file_info) {
  return NULL;
}

static void nautilus_png_convert_menu_provider_iface_init(NautilusMenuProviderIface *iface, gpointer _iface_data) {
  iface->get_background_items = nautilus_png_convert_get_background_items;
  iface->get_file_items = nautilus_png_convert_get_file_items;
}

static void nautilus_png_convert_class_init(NautilusPNGConvertClass *nautilus_png_convert_class, gpointer class_data) {
  parent_class = g_type_class_peek_parent(nautilus_png_convert_class);
}

void nautilus_png_convert_register_type(GTypeModule *module) {
  static const GTypeInfo info = {
    sizeof(NautilusPNGConvertClass),
    (GBaseInitFunc) NULL,
    (GBaseFinalizeFunc) NULL,
    (GClassInitFunc) nautilus_png_convert_class_init,
    (GClassFinalizeFunc) NULL,
    NULL,
    sizeof(NautilusPNGConvert),
    0,
    (GInstanceInitFunc) NULL,
    (GTypeValueTable *) NULL
  };

  static const GInterfaceInfo menu_provider_iface_info = {
    (GInterfaceInitFunc) nautilus_png_convert_menu_provider_iface_init,
    NULL,
    NULL
  };

  png_convert_type = g_type_module_register_type(
    module,
    G_TYPE_OBJECT,
    "NautilusPNGConvert",
    &info,
    0
  );

  g_type_module_add_interface(
    module,
    png_convert_type,
    NAUTILUS_TYPE_MENU_PROVIDER,
    &menu_provider_iface_info
  );
}

GType nautilus_png_convert_get_type(void) {
  return png_convert_type;
}
