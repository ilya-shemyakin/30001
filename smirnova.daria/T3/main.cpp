int main(int argc, char* argv[])
{
  using namespace doroshenko;
  if (argc != 2)
  {
    std::cerr << "Wrong input\n";
    return 1;
  }
  using input_it_t = std::istream_iterator< Polygon >;
  std::ifstream input(argv[1]);
  std::vector< Polygon > polygons;

  while (!input.eof())
  {
    std::copy(input_it_t{ input }, input_it_t{}, std::back_inserter(polygons));
    if (input.fail())
    {
      input.clear();
      input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }

  std::map< std::string, std::function < void(std::vector< Polygon >&, std::istream&, std::ostream&) > > commands;
  {
    using namespace std::placeholders;
    commands["AREA"] = std::bind(doroshenko::cmdArea, _1, _2, _3);
    commands["MAX"] = std::bind(doroshenko::cmdMax, _1, _2, _3);
    commands["MIN"] = std::bind(doroshenko::cmdMin, _1, _2, _3);
    commands["COUNT"] = std::bind(doroshenko::cmdCount, _1, _2, _3);
    commands["RMECHO"] = std::bind(doroshenko::cmdRmecho, _1, _2, _3);
    commands["SAME"] = std::bind(doroshenko::cmdSame, _1, _2, _3);
  }
  auto warningInvCom = std::bind(warning, std::placeholders::_1, "<INVALID COMMAND>\n");

  std::string cmd;
  while (std::cin >> cmd)
  {
    try
    {
      commands.at(cmd)(polygons, std::cin, std::cout);
    }
    catch(const std::invalid_argument& e)
    {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
    catch(const std::out_of_range& e)
    {
      warningInvCom(std::cout);
      std::cin.clear();
      std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
  return 0;
}
