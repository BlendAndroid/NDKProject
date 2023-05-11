#include <stdio.h>
int main(void)
{
    printf("Hello world\n");
    return 0;
}

// 修改文件输出路径到build目录，除了修改tasks.json中的目录，还要修改setting.json中的路径：
// 增加$workspaceRoot/build/
// "c": "cd $dir && gcc $fileName -o $workspaceRoot/build/$fileNameWithoutExt && $workspaceRoot/build/$dir$fileNameWithoutExt",
// "cpp": "cd $dir && g++ $fileName -o $workspaceRoot/build/$fileNameWithoutExt && $workspaceRoot/build/$dir$fileNameWithoutExt",
