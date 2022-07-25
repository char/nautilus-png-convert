#pragma once

#include <glib-object.h>

G_BEGIN_DECLS

#define NAUTILUS_PNG_CONVERT_TYPE (nautilus_png_convert_get_type())
#define NAUTILUS_PNG_CONVERT(o) (G_TYPE_CHECK_INSTANCE_CAST ((o), NAUTILUS_PNG_CONVERT_TYPE, NautilusPNGConvert))
#define NAUTILUS_PNG_CONVERT_IS_NAUTILUS(o) (G_TYPE_CHECK_INSTANCE_TYPE ((o), NAUTILUS_PNG_CONVERT_TYPE))

typedef struct _NautilusPNGConvert NautilusPNGConvert;
typedef struct _NautilusPNGConvertClass NautilusPNGConvertClass;

struct _NautilusPNGConvert {
  GObject __parent;
};

struct _NautilusPNGConvertClass {
  GObjectClass __parent;
};

void nautilus_png_convert_register_type(GTypeModule *module);
GType nautilus_png_convert_get_type(void);

G_END_DECLS
