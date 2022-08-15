class Solution {
public:
    vector<int> sa;
    vector<int> SuffixArray(vector<int> &vi)
    {
        int n=vi.size();
        vector<int> last=vi;
        for(int stp=1,len=1;len/2<n;++stp,len<<=1)
        {
            vector<array<int,3>> curr(n);
            for(int i=0;i<n;++i)
            {
                curr[i][0]=last[i];
                curr[i][1]=(i+len<n ? last[i+len] : -3);
                curr[i][2]=i;
            }
            sort(curr.begin(),curr.end());
            for(int i=0;i<n;++i)
            {
                last[curr[i][2]]=
                    (i>0 && curr[i-1][0]==curr[i][0] && curr[i-1][1]==curr[i][1] ?
                     last[curr[i-1][2]] : i);
            }
        }
        return last;
    }
    int longestCommonSubpath(int n, vector<vector<int>>& paths) {
        vector<int> vp,vi;
        for(int i=0;i<paths.size();++i)
        {
            for(int j=0;j<paths[i].size();++j)
            {
                vp.push_back(paths[i][j]);
                vi.push_back(i);
            }
            vp.push_back(-1);
            vi.push_back(-1);
        }
        sa=SuffixArray(vi);
        
    }
};


2020.01 - 2020.06 芯片驱动软件开发 海思无线终端智慧工程部
开发“可伸缩 taskpool”功能模块。该模块用于封装驱动接口，缓存接收到的计算任务单元、提交给 NPU 进行计算并缓存 NPU 返回的结果。
为了提高调度性能，该模块整体申请一段内存用于分配；并能够根据当前留存的计算任务单元的数量，调整所申请的内存大小。
项目经理 软件工程师
完成功能模块的概要设计和详细设计；完成工具开发、文档写作并交付使用。

2020.01 - 2020.06 芯片驱动软件开发 海思无线终端智慧工程部
Develop the "Scalable taskpool" module. This module is used to cache information of task unit, submit to NPU for calculation, and cache the result returned by NPU.
In order to improve performance, this module applies several contiguous segments of memory for distribution. It also can adjust the size of the applied memory according to the number of currently running computing task units.
项目经理 软件工程师
完成功能模块的概要设计和详细设计；完成工具开发、文档写作并交付使用。

2019.05 - 2019.12 芯片验证 海思无线终端智慧工程部
软件工程师
参与多款芯片投片验证，负责 NPU 安全通路验证，编写测试用例并完成测试。期间针对单板数量有限，调试时间短的问题，使用 Trace32 仿真器，开发工具完成相关用例的测试自动化。

2019.05 - 2019.12 芯片验证 海思无线终端智慧工程部
软件工程师
Participate in the verification of various chips. Responsible for NPU security path verification, write test cases and complete the test.
For short debugging time and very limited number of chips, develop an automation tool based on the Trace32 emulator to achieve test automation.

2018.09 - 2019.04 UndefinedSymbolWarden 工具开发 华为路由器工程部
针对在部署动态库时经常出现的“未定义符号”的问题，开发工具在部署之前进行检查以尽量在运行之前发现未定义符号。
工具解析每个 so 文件中包含的符号及其依赖关系，对其中每个未定义符号尝试从其递归依赖的库中寻找定义。未找到定义的符号将提示用户核查。
系统架构师 项目经理 软件工程师
独立完成工具的概要设计和详细设计；独立完成工具开发、文档写作并交付使用。

For the undefined symbol problem when deploying dynamic libraries, development a tool try to find out undefined symbols before deployment.
The tool parses symbols contained in each so file and its dependencies. for each undefined symbol it tries to find a definition from the libraries it recursively depends on.
If definition is not found, the user will be prompted to check.


2016.07 – 2019.04 静态检查工具调研与开发 华为路由器产品开发部
代码静态检查工具（主要为 coverity/fortify）的调研、落地、配套开发，支撑对代码的质量审查和缺陷发现，并针对代码共性问题进行整改。
软件工程师
完成配套系统部分功能的实现，并在工具上线后进行日常维护。同时针对代码中发现的问题开发相关的 coverity 检查规则进行检测。

The research, implementation, and supporting development of code static inspection tools (mainly coverity/fortify) support code quality review and defect discovery, and rectify code common problems.

2014.09 - 2016.07 嵌入式软件开发 华为路由器产品开发部
模拟路由器 SRounter 是针对路由器设备昂贵，调试困难等情况，对路由器驱动进行模拟，封装底层模拟芯片接口，模拟路由器硬件环境的软件。主要供业务部分开发调试使用。
软件工程师
实现部分功能模块，软件上线后进行维护。

The simulated router SRounter is a software that simulates the router driver, encapsulates the underlying analog chip interface, and simulates the hardware environment of the router for the expensive router equipment and difficult debugging. It is mainly used for the development and debugging of the business part.





