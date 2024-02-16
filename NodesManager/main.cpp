#include <iostream>
#include <tchar.h>
#include "my_interf.h"

using namespace std;
using namespace ENUM_MY_INTERF;

int _tmain(int argc, _TCHAR* argv[])
{
    try
    {
        char sop[32];
        int op;
        my_interf ifc(2, "filedat.bin");

        while (ifc.run)
        {
            ifc.menu();

            cout << "Input number of operation: ";
            cin >> sop;
            op = atoi(sop);

            switch (op)
            {
            case MY_INTERF_PUSH:
                ifc.push();

                break;

            case MY_INTERF_POP:
                ifc.pop();

                break;

            case MY_INTERF_ERASE:
                ifc.erase();

                break;

            case MY_INTERF_CLEAR_ALL:
                ifc.clear_all();

                break;

            case MY_INTERF_EDIT:
                ifc.edit();

                break;

            case MY_INTERF_FIND_ALL:
                ifc.find_all();

                break;

            case MY_INTERF_SAVE_BIN:
                ifc.save_bin();

                break;

            case MY_INTERF_READ_BIN:
                ifc.read_bin();

                break;

            case MY_INTERF_DISPLAY:
                ifc.display();

                break;

            case MY_INTERF_FINISH:
                ifc.finish();

                break;

            default:
                ifc.defaul();
            }
        }
    }
    catch (my_mess exception)
    {
        exception.mess();
        system("pause");
    }

    return 0;
}
