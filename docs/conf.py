# Configuration file for the Sphinx documentation builder.
#
# This file only contains a selection of the most common options. For a full
# list see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Path setup --------------------------------------------------------------

# If extensions (or modules to document with autodoc) are in another directory,
# add these directories to sys.path here. If the directory is relative to the
# documentation root, use os.path.abspath to make it absolute, like shown here.
#
# import os
# import sys
# sys.path.insert(0, os.path.abspath('.'))

# -- Project information -----------------------------------------------------

project = 'myutil'
copyright = '2020, Eason Wang'
author = 'talktoeason@gmail.com'

# The full version, including alpha/beta/rc tags
release = '0.1.0'


# -- General configuration ---------------------------------------------------

# Add any Sphinx extension module names here, as strings. They can be
# extensions coming with Sphinx (named 'sphinx.ext.*') or your custom
# ones.
extensions = [
    # there may be others here already, e.g. 'sphinx.ext.mathjax'
    'breathe',
    'exhale',
    'recommonmark'
]

# Setup the breathe extension
breathe_projects = {
    "myutil": "./doxyoutput/xml"
}
breathe_default_project = "myutil"

# Setup the exhale extension
exhale_args = {
    # These arguments are required
    "containmentFolder":        "./api",
    "rootFileName":             "library_root.rst",
    "rootFileTitle":            "API Reference",
    "doxygenStripFromPath":     "..",
    # Suggested optional arguments
    "createTreeView":           True,
    # TIP: if using the sphinx-bootstrap-theme, you need
    "treeViewIsBootstrap":      True,
    "exhaleExecutesDoxygen":    True,
    "exhaleDoxygenStdin":       "INPUT = ../inc",
    "fullToctreeMaxDepth":      1
}

# Tell sphinx what the primary language being documented is.
primary_domain = 'cpp'

# Tell sphinx what the pygments highlight language should be.
highlight_language = 'cpp'

# Add any paths that contain templates here, relative to this directory.
templates_path = ['_templates']

# List of patterns, relative to source directory, that match files and
# directories to ignore when looking for source files.
# This pattern also affects html_static_path and html_extra_path.
exclude_patterns = []


# -- Options for HTML output -------------------------------------------------

# The theme to use for HTML and HTML Help pages.  See the documentation for
# a list of builtin themes.

import os 
# on_rtd is whether we are on readthedocs.org, this line of code grabbed from docs.readthedocs.org
on_rtd = os.environ.get('READTHEDOCS', None) == 'True'

if not on_rtd:  # only import and set the theme if we're building docs locally
    import sphinx_rtd_theme
    html_theme = 'sphinx_rtd_theme'
    html_theme_path = [sphinx_rtd_theme.get_html_theme_path()]
    print('-'*32)
    print(html_theme)
    print(html_theme_path)
    print('-'*32)
