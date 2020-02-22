#include <iostream>
#include <string>
#include <list>
#include <iterator>
#include "metric2pg.hpp"
#include <boost/program_options.hpp>
using namespace std;

void showlist (list <char*> l) {
    list <char*> :: iterator it;
    for (it = l.begin(); it != l.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << endl;
}

enum List printUsage(int argc, char *argv[])
{

    try
    {
        namespace po = boost::program_options;
        po::options_description desc("Options");

        desc.add_options()  ("help", "Print help messages")
                            ("create", "Create a new RRD")
                            ("update", "Update a RRD")
                            ("updatev", "A verbose version of update")
                            ("graph", "Generate a graph from one or several RRD")
                            ("graphv", "generate a graph from one or several RRD" 
                            "with meta data printed before the graph")
                            ("dump", "Dump a RRD to XML")
                            ("restore", "Restore an RRD file from its XML form")
                            ("last", "Show last update time for RRD")
                            ("lastupdate", "Returns the most recent datum stored for each DS in an RRD")
                            ("first", "Show first update time for RRA within an RRD")
                            ("info", "Returns the configuration and status of the RRD")
                            ("list", "returns the list of RRDs")
                            ("fetch", "Fetch data out of an RRD")
                            ("tune", "Modify some basic properties of an RRD")
                            ("resize", "Alter the length of one of the RRAs in an RRD")
                            ("xport", "Generate XML dump from one or several RRD")
                            ("flushcached", "Flush cached data out to an RRD file")
                            ("ls", "List all *.rrd files in current directory")
                            ("cd", "Change the current directory")
                            ("mkdir", "Create new directory")
                            ("pwd", "Returns the current working directory")
                            ("quit", "Closing a session in remote mode");
        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc),
                      vm); // can throw

            /** --help option 
       */
            if (vm.count("help"))
            {
                std::cout << "Metric2pg 1.0.0" << std::endl;
                std::cout << "Compiled October 25 2019 10:45:27\n"
                          << std::endl;
                std::cout << "Usage: metric2pg [options] command command_options" << std::endl
                          << desc << std::endl;

                std::cout << "\nmetric2pg is distributed under the Terms of the GNU General"
                          << " Public License Version 2. (www.gnu.org/copyleft/gpl.html)" << std::endl;

                return C_NONE;
            }

            if (vm.count("create"))
            {
                std::cout << "\tmetric2pg create filename [--start|-b start time]\n"
                             "\t\t[--step|-s step]\n"
                             "\t\t[--template|-t template-file]\n"
                             "\t\t[--source|-r source-file]\n"
                             "\t\t[--no-overwrite|-O]\n"
                             "\t\t[--daemon|-d address]\n"
                             "\t\t[DS:ds-name:DST:dst arguments]\n"
                             "\t\t[RRA:CF:cf arguments]\n"
                          << std::endl;

                return C_CREATE;
            }

            if (vm.count("update"))
            {
                std::cout << "\tmetric2pg update filename\n"
                             "\t\t[--template|-t ds-name:ds-name:...]\n"
                             "\t\t[--skip-past-updates|-s]\n"
                             "\t\t[--daemon|-d <address>]\n"
                             "\t\ttime|N:value[:value...]\n\n"
                             "\t\tat-time@value[:value...]\n\n"
                             "\t\t[ time:value[:value...] ..]\n"
                          << std::endl;

                return C_UPDATE;
            }

            if (vm.count("updatev"))
            {
                std::cout << "\tmetric2pg updatev filename\n"
                             "\t\t[--template|-t ds-name:ds-name:...]\n"
                             "\t\t[--skip-past-updates|-s]\n"
                             "\t\ttime|N:value[:value...]\n\n"
                             "\t\tat-time@value[:value...]\n\n"
                             "\t\t[ time:value[:value...] ..]\n"
                          << std::endl;

                return C_UPDATEV;
            }

            if (vm.count("graph"))
            {
                std::cout << "\tmetric2pg graph filename [-s|--start seconds] [-e|--end seconds]\n"
                          << std::endl;

                /* graph1 */

                std::cout << "\t\t[-x|--x-grid x-axis grid and label]\n"
                             "\t\t[-Y|--alt-y-grid] [--full-size-mode]\n"
                             "\t\t[--left-axis-format format]\n"
                             "\t\t[-y|--y-grid y-axis grid and label]\n"
                             "\t\t[-v|--vertical-label string] [-w|--width pixels]\n"
                             "\t\t[--right-axis scale:shift] [--right-axis-label label]\n"
                             "\t\t[--right-axis-format format]\n"
                             "\t\t[-h|--height pixels] [-o|--logarithmic]\n"
                             "\t\t[-u|--upper-limit value] [-z|--lazy]\n"
                             "\t\t[-l|--lower-limit value] [-r|--rigid]\n"
                             "\t\t[-g|--no-legend] [-d|--daemon <address>]\n"
                             "\t\t[-F|--force-rules-legend]\n"
                             "\t\t[-j|--only-graph]\n"
                          << std::endl;

                /* graph2 */

                std::cout << "\t\t[-n|--font FONTTAG:size:font]\n"
                             "\t\t[-m|--zoom factor]\n"
                             "\t\t[-A|--alt-autoscale]\n"
                             "\t\t[-M|--alt-autoscale-max]\n"
                             "\t\t[-G|--graph-render-mode {normal,mono}]\n"
                             "\t\t[-R|--font-render-mode {normal,light,mono}]\n"
                             "\t\t[-B|--font-smoothing-threshold size]\n"
                             "\t\t[-T|--tabwidth width]\n"
                             "\t\t[-E|--slope-mode]\n"
                             "\t\t[-P|--pango-markup]\n"
                             "\t\t[-N|--no-gridfit]\n"
                             "\t\t[-X|--units-exponent value]\n"
                             "\t\t[-L|--units-length value]\n"
                             "\t\t[-S|--step seconds]\n"
                             "\t\t[-f|--imginfo printfstr]\n"
                             "\t\t[-a|--imgformat PNG]\n"
                             "\t\t[-c|--color COLORTAG#rrggbb[aa]]\n"
                             "\t\t[--border width\n"
                             "\t\t[-t|--title string]\n"
                             "\t\t[-W|--watermark string]\n"
                             "\t\t[-Z|--use-nan-for-all-missing-data]\n"
                             "\t\t[DEF:vname=rrd:ds-name:CF]\n"
                          << std::endl;

                /* graph3 */

                std::cout << "\t\t[CDEF:vname=rpn-expression]\n"
                             "\t\t[VDEF:vdefname=rpn-expression]\n"
                             "\t\t[PRINT:vdefname:format]\n"
                             "\t\t[GPRINT:vdefname:format]\n"
                             "\t\t[COMMENT:text]\n"
                             "\t\t[SHIFT:vname:offset]\n"
                             "\t\t[TEXTALIGN:{left|right|justified|center}]\n"
                             "\t\t[TICK:vname#rrggbb[aa][:[fraction][:legend]]]\n"
                             "\t\t[HRULE:value#rrggbb[aa][:legend]]\n"
                             "\t\t[VRULE:value#rrggbb[aa][:legend]]\n"
                             "\t\t[LINE[width]:vname[#rrggbb[aa][:[legend][:STACK]]]]\n"
                             "\t\t[AREA:vname[#rrggbb[aa][:[legend][:STACK]]]]\n"
                             "\t\t[PRINT:vname:CF:format] (deprecated)\n"
                             "\t\t[GPRINT:vname:CF:format] (deprecated)\n"
                             "\t\t[STACK:vname[#rrggbb[aa][:legend]]] (deprecated)\n"
                          << std::endl;

                return C_GRAPH;
            }

            if (vm.count("graphv"))
            {
                std::cout << "\tmetric2pg graphv filename [-s|--start seconds] [-e|--end seconds]\n"
                          << std::endl;

                /* graph1 */

                std::cout << "\t\t[-x|--x-grid x-axis grid and label]\n"
                             "\t\t[-Y|--alt-y-grid] [--full-size-mode]\n"
                             "\t\t[--left-axis-format format]\n"
                             "\t\t[-y|--y-grid y-axis grid and label]\n"
                             "\t\t[-v|--vertical-label string] [-w|--width pixels]\n"
                             "\t\t[--right-axis scale:shift] [--right-axis-label label]\n"
                             "\t\t[--right-axis-format format]\n"
                             "\t\t[-h|--height pixels] [-o|--logarithmic]\n"
                             "\t\t[-u|--upper-limit value] [-z|--lazy]\n"
                             "\t\t[-l|--lower-limit value] [-r|--rigid]\n"
                             "\t\t[-g|--no-legend] [-d|--daemon <address>]\n"
                             "\t\t[-F|--force-rules-legend]\n"
                             "\t\t[-j|--only-graph]\n"
                          << std::endl;

                /* graph2 */

                std::cout << "\t\t[-n|--font FONTTAG:size:font]\n"
                             "\t\t[-m|--zoom factor]\n"
                             "\t\t[-A|--alt-autoscale]\n"
                             "\t\t[-M|--alt-autoscale-max]\n"
                             "\t\t[-G|--graph-render-mode {normal,mono}]\n"
                             "\t\t[-R|--font-render-mode {normal,light,mono}]\n"
                             "\t\t[-B|--font-smoothing-threshold size]\n"
                             "\t\t[-T|--tabwidth width]\n"
                             "\t\t[-E|--slope-mode]\n"
                             "\t\t[-P|--pango-markup]\n"
                             "\t\t[-N|--no-gridfit]\n"
                             "\t\t[-X|--units-exponent value]\n"
                             "\t\t[-L|--units-length value]\n"
                             "\t\t[-S|--step seconds]\n"
                             "\t\t[-f|--imginfo printfstr]\n"
                             "\t\t[-a|--imgformat PNG]\n"
                             "\t\t[-c|--color COLORTAG#rrggbb[aa]]\n"
                             "\t\t[--border width\n"
                             "\t\t[-t|--title string]\n"
                             "\t\t[-W|--watermark string]\n"
                             "\t\t[-Z|--use-nan-for-all-missing-data]\n"
                             "\t\t[DEF:vname=rrd:ds-name:CF]\n"
                          << std::endl;

                /* graph3 */

                std::cout << "\t\t[CDEF:vname=rpn-expression]\n"
                             "\t\t[VDEF:vdefname=rpn-expression]\n"
                             "\t\t[PRINT:vdefname:format]\n"
                             "\t\t[GPRINT:vdefname:format]\n"
                             "\t\t[COMMENT:text]\n"
                             "\t\t[SHIFT:vname:offset]\n"
                             "\t\t[TEXTALIGN:{left|right|justified|center}]\n"
                             "\t\t[TICK:vname#rrggbb[aa][:[fraction][:legend]]]\n"
                             "\t\t[HRULE:value#rrggbb[aa][:legend]]\n"
                             "\t\t[VRULE:value#rrggbb[aa][:legend]]\n"
                             "\t\t[LINE[width]:vname[#rrggbb[aa][:[legend][:STACK]]]]\n"
                             "\t\t[AREA:vname[#rrggbb[aa][:[legend][:STACK]]]]\n"
                             "\t\t[PRINT:vname:CF:format] (deprecated)\n"
                             "\t\t[GPRINT:vname:CF:format] (deprecated)\n"
                             "\t\t[STACK:vname[#rrggbb[aa][:legend]]] (deprecated)\n"
                          << std::endl;

                return C_GRAPHV;
            }

            if (vm.count("dump"))
            {
                std::cout << "\tmetric2pg dump [--header|-h {none,xsd,dtd}]\n"
                             "\t\t[--no-header|-n]\n"
                             "\t\t[--daemon|-d address]\n"
                             "\t\tfile.rrd [file.xml]"
                          << std::endl;

                return C_DUMP;
            }

            if (vm.count("restore"))
            {
                std::cout << "\tmetric2pg restore [--range-check|-r] [--force-overwrite|-f] filename.xml filename.rrd\n"
                          << std::endl;

                return C_RESTORE;
            }

            if (vm.count("last"))
            {
                std::cout << "\tmetric2pg last filename.rrd\n"
                             "\t\t[--daemon|-d address]\n"
                          << std::endl;

                return C_LAST;
            }

            if (vm.count("lastupdate"))
            {
                std::cout << "\tmetric2pg lastupdate filename.rrd\n"
                             "\t\t[--daemon|-d address]\n"
                          << std::endl;

                return C_LASTUPDATE;
            }

            if (vm.count("first"))
            {
                std::cout << "\tmetric2pg first filename.rrd [--rraindex number] [--daemon|-d address]\n"
                          << std::endl;

                return C_FIRST;
            }

            if (vm.count("info"))
            {
                std::cout << "\tmetric2pg info [--daemon|-d <addr> [--noflush|-F]] filename.rrd\n"
                          << std::endl;

                return C_INFO;
            }

            if (vm.count("list"))
            {
                std::cout << "\tmetric2pg list [--daemon <address>] [--noflush] <dirname>\n"
                          << std::endl;

                return C_LIST;
            }

            if (vm.count("fetch"))
            {
                std::cout << "\tmetric2pg fetch filename.rrd CF\n"
                             "\t\t[-r|--resolution resolution]\n"
                             "\t\t[-s|--start start] [-e|--end end]\n"
                             "\t\t[-a|--align-start]\n"
                             "\t\t[-d|--daemon <address>]\n"
                          << std::endl;

                return C_FETCH;
            }

            if (vm.count("tune"))
            {
                /* tune1 */

                std::cout << "\tmetric2pg tune filename\n"
                             "\t\t[--heartbeat|-h ds-name:heartbeat]\n"
                             "\t\t[--data-source-type|-d ds-name:DST]\n"
                             "\t\t[--data-source-rename|-r old-name:new-name]\n"
                             "\t\t[--minimum|-i ds-name:min] [--maximum|-a ds-name:max]\n"
                             "\t\t[--deltapos|-p scale-value] [--deltaneg|-n scale-value]\n"
                             "\t\t[--failure-threshold|-f integer]\n"
                             "\t\t[--window-length|-w integer]\n"
                             "\t\t[--alpha|-x adaptation-parameter]\n"
                          << std::endl;

                /* tune2 */

                std::cout << "\t\t[--beta|-y adaptation-parameter]\n"
                             "\t\t[--gamma|-z adaptation-parameter]\n"
                             "\t\t[--gamma-deviation|-v adaptation-parameter]\n"
                             "\t\t[--smoothing-window|-s fraction-of-season]\n"
                             "\t\t[--smoothing-window-deviation|-S fraction-of-season]\n"
                             "\t\t[--aberrant-reset|-b ds-name]\n"
                          << std::endl;

                /* tune3 */

                std::cout << "\t\t[--step|-t newstep]\n"
                             "\t\t[--daemon|-D address]\n"
                             "\t\t[DEL:ds-name]\n"
                             "\t\t[DS:ds-spec]\n"
                             "\t\t[DELRRA:index]\n"
                             "\t\t[RRA:rra-spec]\n"
                             "\t\t[RRA#index:[+-=]number]\n"
                          << std::endl;

                return C_TUNE;
            }

            if (vm.count("resize"))
            {
                std::cout << "\tmetric2pg resize filename rranum GROW|SHRINK rows\n"
                          << std::endl;

                return C_RESIZE;
            }

            if (vm.count("xport"))
            {
                std::cout << "\tmetric2pg xport [-s|--start seconds] [-e|--end seconds]\n"
                             "\t\t[-m|--maxrows rows]\n"
                             "\t\t[--step seconds]\n"
                             "\t\t[-t|--showtime]\n"
                             "\t\t[--enumds] [--json]\n"
                             "\t\t[-d|--daemon address]\n"
                             "\t\t[DEF:vname=rrd:ds-name:CF]\n"
                             "\t\t[CDEF:vname=rpn-expression]\n"
                             "\t\t[XPORT:vname:legend]\n"
                          << std::endl;

                return C_XPORT;
            }

            if (vm.count("flushcached"))
            {
                std::cout << "\tmetric2pg flushcached filename.rrd\n"
                             "\t\t[-d|--daemon <address>]\n"
                          << std::endl;

                return C_FLUSHCACHED;
            }

            if (vm.count("ls"))
            {
                std::cout << "\tmetric2pg ls\n"
                          << std::endl;

                return C_LS;
            }

            if (vm.count("pwd"))
            {
                std::cout << "\tmetric2pg pwd\n"
                          << std::endl;

                return C_PWD;
            }

            if (vm.count("cd"))
            {
                std::cout << "\trrdtool cd directoryname\n"
                          << std::endl;

                return C_CD;
            }

            if (vm.count("mkdir"))
            {
                std::cout << "\trrdtool mkdir newdirectoryname\n"
                          << std::endl;

                return C_MKDIR;
            }

            if (vm.count("quit"))
            {
                std::cout << "\trrdtool quit\n"
                          << std::endl;

                return C_QUIT;
            }

            po::notify(vm); // throws on error, so do after help in case
                            // there are any problems
        }
        catch (po::error &e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl
                      << std::endl;
            std::cerr << desc << std::endl;
            return C_NONE;
        }
    }
    catch (std::exception &e)
    {
        std::cerr << "Unhandled Exception reached the top of main: "
                  << e.what() << ", application will now exit" << std::endl;
        return C_NONE;
    }

    return C_NONE;
}

int main(int argc, char *argv[])
{

    List cmd = printUsage(argc, argv);
    int return_code;
    std::list <char*> arguments;

    for (int i = 2; i < argc; i++) {
        arguments.push_back(argv[i]);
    }

    switch (cmd)
    {
    case C_CREATE:
        return_code = metric2pg_create(arguments);
        if (return_code == -1) {
            return -1;
        }
        break;
    case C_UPDATE:
        return_code = metric2pg_update(arguments);
        if (return_code == -1) {
            return -1;
        }
        break;
    case C_FETCH:
        return_code = metric2pg_fetch(arguments);
        if (return_code == -1) {
            return -1;
        }
        break;
    case C_DUMP:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_INFO:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_LIST:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_RESTORE:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_LAST:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_LASTUPDATE:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_FIRST:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_GRAPH:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_GRAPHV:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_TUNE:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_RESIZE:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_XPORT:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_UPDATEV:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_FLUSHCACHED:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_LS:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_CD:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_MKDIR:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_PWD:
        std::cout << "Not implemented yet" << std::endl;
        break;
    case C_QUIT:
        std::cout << "Not implemented yet" << std::endl;
        break;

    default:
        break;
    }

    return 0;
}
