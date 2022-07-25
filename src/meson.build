nautilus_png_convert_sources = [
  'nautilus-png-convert-module.c',
  'nautilus-png-convert.c',
]

nautilus_png_convert_headers = [
  'nautilus-png-convert.h',
]

libnautilus_extension = dependency('libnautilus-extension', version: '>= 42.2')
nautilus_ext_dir = libnautilus_extension.get_variable('extensiondir')

nautilus_png_convert_deps = [
  dependency('glib-2.0', version: '>= 2.44'),
  libnautilus_extension,
]

cc = meson.get_compiler('c')

add_project_arguments(
  cc.get_supported_arguments(
    [
      '-Wno-unused-parameter',
    ],
  ),
  language: 'c',
)

nautilus_png_convert_lib = shared_library('nautilus-png-convert',
  nautilus_png_convert_sources,
  nautilus_png_convert_headers,
  dependencies: nautilus_png_convert_deps,
  install: true,
  install_dir: nautilus_ext_dir,
)
