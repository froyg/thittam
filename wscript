
APPNAME = 'thittam'
VERSION = '0.1'

import os
from os import path

top = '.'
out = 'build'

def options(opt):
    opt.load('compiler_cxx boost')
    opt.add_option("--enable-debug", action="store_true", default=False,
                   help="Enable debug build")
    opt.add_option("--release-version", default='debug-version',
                   dest="release_version", type='string')
    opt.add_option("--release-build", action="store_true", default=False,
                   help="Build for release")

def configure(conf):
    conf.load('compiler_cxx boost')
    conf.env.ENABLE_DEBUG_BUILD = conf.options.enable_debug
    conf.env.RELEASE_VERSION = conf.options.release_version
    conf.env.APP_NAME = "thittam"

    # configure the resource-directory
    resource_dir = ""
    if conf.options.release_build:
        resource_dir = path.join (conf.options.prefix, "share", conf.env.APP_NAME)
    else:
        resource_dir = path.join (conf.srcnode.abspath(), "src", "resources")
    conf.env.RESOURCE_DIR = resource_dir

    conf.env.prepend_value('CXXFLAGS', ['-std=gnu++11', '-Wall', '-Werror',
                                        '-Wno-error=unused-local-typedefs'])

    boost_opts = { 'lib' : ['date_time', 'program_options', 'thread',
                            'filesystem', 'system'] }
    if 'BOOST_ROOT' in os.environ:
        boost_opts['includes'] = os.environ['BOOST_ROOT'] + '/include'
        boost_opts['libs'] = os.environ['BOOST_ROOT'] + '/lib'
    conf.check_boost(**boost_opts)
    conf.env.append_value('DEFINES_BOOST', 'BOOST_FILESYSTEM_VERSION=3')

    # pkg-config based libs
    conf.check_cfg(
        package="gtkmm-3.0", uselib_store="GTKMM",
        args=['--cflags', '--libs']
        )

    # other pkg-config based libs
    conf.check_cfg(
        package="hdb-log", uselib_store="HDB_LOG",
        args=['--cflags', '--libs']
        )

def build(bld):
    bld.recurse('gmock')
    bld.recurse('src')
    bld.add_group()
    bld.recurse('tests')

# Local Variables:
# mode: python
# indent-tabs-mode: nil
# tab-width: 4
# End:
