#include <iostream>
#include <boost/program_options.hpp>
using namespace std;

void printUsage(int argc, char **argv)
{

    try
    {
        namespace po = boost::program_options;
        po::options_description desc("Options");

        desc.add_options()
            ("help", "Print help messages")
            ("create", "Create a new RRD")
            ("update", "Update a RRD")
            ("updatev", "A verbose version of update")
            ("graph", "Generate a graph from one or several RRD")
            ("graphv", "generate a graph from one or several RRD\n"
                "with meta data printed before the graph")
            ("dump", "Dump a RRD to XML")
            ("restore", "Restore an RRD file from its XML form")
            ("last", "Show last update time for RRD")
            ("lastupdate", "eturns the most recent datum stored for each DS in an RRD")
            ("first", "Show first update time for RRA within an RRD")
            ("info", "Returns the configuration and status of the RRD")
            ("list", "returns the list of RRDs")
            ("fetch", "Fetch data out of an RRD")
            ("tune", "Modify some basic properties of an RRD")
            ("resize", "Alter the length of one of the RRAs in an RRD")
            ("xport", "generate XML dump from one or several RRD")
            ("flushcached", "flush cached data out to an RRD file");

        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc),
                      vm); // can throw

            /** --help option 
       */
            if (vm.count("help"))
            {
                std::cout << "Metric2pg 1.0.0" <<std::endl; 
                std::cout << "Compiled October 25 2019 10:45:27\n" << std::endl;
                std::cout << "Usage: metric2pg [options] command command_options" <<std::endl << desc << std::endl;
                
                std::cout << "\nmetric2pg is distributed under the Terms of the GNU General"
                <<" Public License Version 2. (www.gnu.org/copyleft/gpl.html)" << std::endl;
            }

            po::notify(vm); // throws on error, so do after help in case
                            // there are any problems
        }
        catch (po::error &e)
        {
            std::cerr << "ERROR: " << e.what() << std::endl
                      << std::endl;
            std::cerr << desc << std::endl;
            return;
        }

        // application code here //
    }
    catch (std::exception &e)
    {
        std::cerr << "Unhandled Exception reached the top of main: "
                  << e.what() << ", application will now exit" << std::endl;
        return;
    }
}

int main(int argc, char **argv)
{

    printUsage(argc, argv);
    cout << "hello world!" << endl;
    return 0;
}
