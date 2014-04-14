#include <boost/python.hpp>
#include <iostream>

//游戏初始化
int game_init() {
    return 0;
}

//游戏开始后死循环
int game_run() {
    return 0;
}

//游戏退出
int game_over() {
    return 0;
}

int main(int, char **) {
      using namespace boost::python;

      Py_Initialize();
      std::cout << "Python 解释器实例化完毕!" << std::endl;
      std::string filename = "crot";
      std::string methodname_start = "start";
      std::string methodname_resume = "resume";

      PyRun_SimpleString("import sys");
      PyRun_SimpleString("sys.path.append('./plib')");

      std::cout << "Python 开始执行1!" << std::endl;
      PyObject * pyFileName = PyString_FromString(filename.c_str());
      std::cout << "Python 开始执行2!" << std::endl;
      PyObject * pyMod = PyImport_Import(pyFileName);
      std::cout << "Python 开始执行3!" << std::endl;
      if(pyMod ==NULL ){
          std::cout << "导入失败!" << std::endl;
          return -1;
      }
      PyObject * pyFunc_mix = PyObject_GetAttrString(pyMod, methodname_start.c_str());

      if(pyFunc_mix ==NULL ){
                std::cout << "获取函数失败!" << std::endl;
                return -2;
            }
      std::cout << "Python 开始执行!" << std::endl;
      if(pyFunc_mix && PyCallable_Check(pyFunc_mix)) {
             PyObject * pyParams = PyTuple_New(1);
             PyTuple_SetItem(pyParams, 0, Py_BuildValue("i", 5));
             PyObject_CallObject(pyFunc_mix, pyParams);
      }
        std::cout << "Python START!" << std::endl;

  PyObject * pyFunc_resume = PyObject_GetAttrString(pyMod, methodname_resume.c_str());
  int count = 6;
  int r1 = 0;
  while(count>0) {
       if(pyFunc_resume && PyCallable_Check(pyFunc_resume)) {
             PyObject * pyValue = PyObject_CallObject(pyFunc_resume, NULL);
             if(pyValue == NULL){
                break;
             }
             PyArg_Parse(pyValue, "i", &r1);
             std::cout << "Now IN C++! The Result is " << r1<< std::endl;
        }
        count--;
  }
  Py_Finalize();
  return 0;
}
