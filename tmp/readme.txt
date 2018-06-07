Scanner类接口说明：
	请在所需的域内（建议在全局域内）构造一个scanner对象。
	可以通过Scanner（ifstream&）构造，适用于脚本解释；
	也可以通过Scanner（istream&）或默认构造，适用于交互式解释；
	使用void stream_input(istream&)函数以动态输入新的代码；
	使用tuple<Symbol,int,double,string> return_output()函数以得到返回结果；
	返回值为一个四元组，分别为符号类型、整数数值（如果是整数）、浮点数数值（如果是浮点数）、词的原始内容（如果词本身是string常量，则返回的是其内容）；
	使用bool is_empty()函数以检查代码是否分析完毕；

Symbol枚举类型说明：
	定义在全局域内，具体请参看Symbol.h;
	一些符号使用其英文，如at表示@；
	一些c++内也有的保留字加上后缀表示，如and_py;
	不一定全面，如有需要可以再建；

测试说明：
	提供了两个简单的程序，可以测试该Scanner类的功能；
	分别为DynamicTest和ScriptTest；
	可以参看其源代码以了解Scanner的用法；
	编译指令可以参看makefile；
	