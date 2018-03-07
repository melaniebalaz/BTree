 // simpletest.C
 // 
 // UE Algorithmen und Datenstrukturen - SS 2016 Universitaet Wien
 // Container - Projekt
 // https://cewebs.cs.univie.ac.at/ADS/ss16/
 //
 // Simples Testprogramm zur Ueberpruefung der Container-Funktionalitaet
 //
 // BEACHTEN:
 // (1) Die Zeichenfolge Btree ist in der ganzen Datei durch den Klassennamen 
 //     der Implementierung zu ersetzen (auch im #include).
 // (2) Der Elementdatentyp muss mit Compileroption -DETYPE=<typ> festgelegt werden,
 //     also zb -DETYPE=std::string
 // (3) Der zweite Templateparameter kann mit Compileroption -DSIZE=<n> festgelegt
 //     werden, also zb -DSIZE=13, andernfalls wird der Defaultwert verwendet.
 // (4) Das Testprogramm testet nicht alle Container-Methoden, es kann aber entsprechend
 //     erweitert werden.
 // 
 // g++ -Wall -O3 --std=c++11 --pedantic-errors -DETYPE=std::string simpletest.C
 // g++ -Wall -O3 --std=c++11 --pedantic-errors -DETYPE=std::string -DSIZE=13 simpletest.C
 
 #include <iostream>
 #include <sstream>
 #include <fstream>
 #include <string>
 #include <cstring>
 #include <cstdlib>
 #include <cctype>
 #include "../upload/Btree.h"
 
 #ifndef ETYPE 
#endif
 
 class Person;
 using ElementType = size_t;
 
 const char helpstr[] = 
   "new ............................... create new Container\n"
   "delete ............................ delete Container\n"
   "add <key> [...] ................... add <key>(s) with Container::add(int)\n"
   "remove <key> [...] ................ remove <key>(s) with Container::remove(int)\n"
   "member <key> ...................... call Container::member(<key>)\n"
   "size .............................. call Container::size()\n"
   "empty ............................. call Container::empty()\n"
   "min ............................... call Container::min()\n"
   "max ............................... call Container::max()\n"
   "print ............................. print container with operator<<()\n"
   "apply [asc|desc|dontcare [<n>]] ... traverse container with apply (throw exception in nth call)\n"
   "trace ............................. toggle tracing on/off\n"
   "fadd <filename> ................... add values read from file <filename>\n"
   "fremove <filename> ................ remove values read from file <filename>\n"
   "radd [<n> [<seed>]] ............... add <n> random values, optionally reset generator to <seed>\n"
   "rremove [<n> [<seed>]] ............ remove <n> random values, optionally reset generator to <seed>\n"
   "quit .............................. quit program\n\n"
   "arguments surrounded by [] are optional\n";
 
 void setrandom(int seed) { srand(seed); }
 template <typename E> E nextrandom() { return E(rand()); }
 
 // Template-Spezialisierungen fuer Klasse std::string
 
 template <> inline double doubleValue(const std::string& e) {
   double rc = 0.; for (size_t i = e.length(); i--;) rc /= 256., rc += e[i]; return rc;
 }
 template <> inline size_t hashValue(const std::string& e) { return std::hash<std::string>()(e); }
 template <> std::string nextrandom() {
   std::string rc;
   for (int i = rand() / (RAND_MAX/4+1) + 4; i; --i) rc += char(rand() / (RAND_MAX/('z'-'a'+1) + 1) + 'a');
   return rc;
 }

 // Klasse Person mit allen für die Verwendung als Container-Elementdatentyp noetigen Methoden und Funktionen
 
 class Person {
   std::string vorname;
   std::string nachname;
 public:
   Person() { }
   Person(std::string vorname, std::string nachname) : vorname(vorname), nachname(nachname) { }
   bool operator==(const Person& p) const { return vorname == p.vorname && nachname == p.nachname; }
   bool operator>(const Person& p) const { return nachname > p.nachname || (nachname == p.nachname && vorname > p.vorname); }
 
   std::ostream& print(std::ostream& o) const { return o << '[' << nachname << ", " << vorname << ']'; }
   std::istream& read(std::istream& i) { return i >> vorname >> nachname; }
   friend double doubleValue<Person>(const Person& e);
   friend size_t hashValue<Person>(const Person& e);
   friend size_t ordinalValue<Person>(const Person& e);
 };
 
 inline std::ostream& operator<<(std::ostream& o, const Person& p) { return p.print(o); }
 inline std::istream& operator>>(std::istream& i, Person& p) { return p.read(i); }
 
 // Template-Spezialisierungen fuer Klasse Person
 
 template <> inline double doubleValue(const Person& e) { return doubleValue(e.nachname); }
 template <> inline size_t hashValue(const Person& e) { return hashValue(e.nachname) ^ hashValue(e.vorname); }
 template <> Person nextrandom() { return Person(nextrandom<std::string>(), nextrandom<std::string>()); }
 
 bool match(const std::string& s, const char * c) {
   return c && s.length() > 0 && s.length() <= std::strlen(c) && s.compare(0, s.length(), c, s.length()) == 0;
 }

 std::istream& operator>>(std::istream& i, Order& o) {
   std::string str;
   i >> str;
   o = match(str, "ascending") ? ascending : match(str, "descending") ? descending : dontcare;
   return i;
 }

 class ApplyTestException : public std::exception {
 public:
   virtual const char * what() const noexcept override { return "exception not properly catched in apply()"; }
 };
 
 int main() {
 
   Container<ElementType>* c = nullptr;
   bool traceIt = false;
   std::cout.setf(std::ios_base::boolalpha);
 
   while (true) {
     if (traceIt) {
       if (c) {
         std::cout << std::endl << "container:\n" << *c;
       } else {
         std::cout << std::endl << "no container";
       }
     }
     std::cout << std::endl << "> ";
 
     std::string cmdline;
     if (!std::getline(std::cin, cmdline)) break;
 
     std::istringstream cmdstream(cmdline);
     std::string cmd;
 
     cmdstream >> cmd;
 
     try {
       if (cmd.length() == 0) {
       } else if (match(cmd, "quit")) {
         break;
       } else if (match(cmd, "new")) {
         if (c) {
           std::cerr << "container exists, 'delete' it first";
         } else {
#ifdef SIZE
           c = new Btree<ElementType,SIZE>;
#else
           c = new Btree<ElementType>;
#endif
         }
       } else if (match(cmd, "help") || cmd == "?") {
         std::cout << helpstr;
       } else if (match(cmd, "trace")) {
         std::cout << "trace " << ((traceIt = !traceIt) ? "on" : "off");
       } else if (!c) {
         std::cout << "no container (use 'new')";
       } else {
         ElementType key;
         if (match(cmd, "delete")) {
           delete c;
           c = 0;
         } else if (match(cmd, "add")) {
           while (cmdstream >> key) { c->add(key); }
         } else if (match(cmd, "remove")) {
           while (cmdstream >> key) { c->remove(key); }
         } else if (match(cmd, "member")) {
           cmdstream >> key;
           std::cout << "returns " << c->member(key);
         } else if (match(cmd, "size")) {
           std::cout << "returns " << c->size();
         } else if (match(cmd, "empty")) {
           std::cout << "returns " << c->empty();
         } else if (match(cmd, "min")) {
           std::cout << "returns " << c->min();
         } else if (match(cmd, "max")) {
           std::cout << "returns " << c->max();
         } else if (match(cmd, "print")) {
           std::cout << *c;
         } else if (match(cmd, "apply")) {
           int n = 0;
           Order order;
           cmdstream >> order >> n;
           size_t rc1 = c->apply([&](const ElementType& e) {
             if (n>0 && !--n) throw ApplyTestException(); // test exception handling of apply()
             std::cout << e << ' ';
           }, order);
           std::cout << "\nreturns " << rc1;
         } else if (match(cmd, "fadd")) {
           std::string filename;
           cmdstream >> filename;
           std::ifstream keystream(filename.c_str());
           while (keystream >> key) { c->add(key); }
         } else if (match(cmd, "fremove")) {
           std::string filename;
           cmdstream >> filename;
           std::ifstream keystream(filename.c_str());
           while (keystream >> key) { c->remove(key); }
         } else if (match(cmd, "radd")) {
           int seed = -1, count = 1;
           cmdstream >> count >> seed;
           if (seed != -1) setrandom(seed);
           while (count-- > 0) c->add(nextrandom<ElementType>());
         } else if (match(cmd, "rremove")) {
           int seed = -1, count = 1;
           cmdstream >> count >> seed;
           if (seed != -1) setrandom(seed);
           while (count-- > 0) c->remove(nextrandom<ElementType>());
         } else {
           std::cout << cmd << "? try 'help'";
         }
       }
     } catch (ContainerException& e) {
       std::cout << "catched ContainerException \"" << e.what() << "\"";
     } catch (std::exception& e) {
       std::cout << "catched std::exception \"" << e.what() << "\"";
     } catch (...) {
       std::cout << "OOPS! - catched something else";
     }
   }
   return 0;
 }

