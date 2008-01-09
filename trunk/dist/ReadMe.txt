svn_wcstatus - Subversion working copy status
A content plugin for Total Commander
http://svnwcstatus.berlios.de/

Description
===========
svn_wcstatus is a content plugin for the popular shareware file manager Total
Commander (see http://www.ghisler.com/) for Microsoft Windows® operating
systems. svn_wcstatus provides detailed information about the status of
Subversion working copies (see http://subversion.tigris.org/), enabling Total
Commanders's built-in features to use the status for displaying, sorting,
(regex-)searching, multi-renaming and more.

Installation
============
svn_wcstatus relies on the libraries APR, APR-util and APR-iconv (see
http://apr.apache.org/), as Subversion does. In order to use svn_wcstatus,
these libraries have to be installed properly on your system. If you are
familiar whith the APR libraries, and you are sure that they are installed
on your system, you can simply skip the APR paragraph.

Plugin installation:
The zip archive should be "auto-installabe" by Total Commander. However, if
you prefer to install svn_wcstatus manually, here are some short instructions.

1) Create subdirectory "svn_wcstatus" or similar somewhere on your harddisk
2) Extract the contents of the zip archive to the above directory
3) Select Configuration -> Options -> Operation
4) Click on Content plugins and add svn_wcstatus.wdx

APR installation:
APR, APR-util and APR-iconv are not included in the svn_wcstatus zip archive,
since APR-iconv is pretty big in size, and the installation of APR needs some
human interaction when not providing an ee-installer. You can download the
appropriate versions for svn_wcstatus from the BerliOS project page at
http://developer.berlios.de/projects/svnwcstatus/. The DLLs have to be placed
in a directory contained in your PATH environment variable, or directly in the
Total Commander folder. You can place the iconv directory directly in the
directory into which you installed svn_wcstatus. In this case, the plugin
should be clever enough to set up the environment correctly itself. If that
doesn't work, or is undesired, simply point the APR_ICONV_PATH environment
variable to the iconv folder on your harddrive.
Note on TortoiseSVN's versions of the APR libs: TortoiseSVN uses its own,
patched versions of APR, which are incompatible to the original versions used
by svn_wctatus. Don't try to use the APR libs provided by TortoiseSVN in
conjunction with svn_wcstatus. It probably won't work.

Finished!
If all went well, you should now be able to access the Subversion working copy
status via the custom columns feature, the "Plugins" Tab in the Find Files
dialog, and everywhere else where you can access content plugin columns in
Total Commander.


Configuration
=============
Threre are some configuration options available. You may want to take a look
into the svn_wcstatus.ini file in the subdirectory where your Total Commander
INI files reside.


Licensing
=========
This product includes software developed by CollabNet (http://www.collab.net/).
The zip archive should contain the legal documents of svn_wcstatus and its
libraries in several LICENSE files. svn_wcstatus itself is licensed under the
GNU General Public License, version 3. As I am no expert in open source
licensing, I cannot guarantee that there are some issues using all these
different licenses together in this project. If you think that svn_wcstatus
violates the licenses used by its libraries in some way, or that the GPL
forbids the usage of svn_wcstatus in the intended way, please contact me and
explain your concerns.


Contact
=======
If you have problems or suggestions concerning svn_wcstatus, please feel free
to contact me via the BerliOS project page or via E-Mail (wieczorek@gmx.net).
http://developer.berlios.de/projects/svnwcstatus/.

History
=======
2008-01-09 svn_wcstatus version 0.1.0
 - based on Subversion 1.4.6, neon 0.26.4, zlib 1.2.3,
   apr 0.9.17, apr-util 0.9.15, apr-iconv 0.9.7
 - initial version
