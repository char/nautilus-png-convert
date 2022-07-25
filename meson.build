project('nautilus-png-convert', 'c', version: '0.5.0',
  meson_version: '>= 0.59.0',
  default_options: [
    'buildtype=debugoptimized',
    'warning_level=3',
    'c_std=c18',
  ],
)

config_h = configuration_data()
config_h.set_quoted('PACKAGE_NAME', meson.project_name())
config_h.set_quoted('PACKAGE_VERSION', meson.project_version())
config_h.set_quoted('PACKAGE_STRING', '@0@ @1@'.format(meson.project_name(), meson.project_version()))

configure_file(
  output: 'nautilus-png-convert-config.h',
  configuration: config_h,
)

add_project_arguments([ '-I' + meson.project_build_root(), ], language: 'c')

subdir('src')
