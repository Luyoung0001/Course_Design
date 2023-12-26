# 数据结构课程设计
## 哈夫曼编/译码器
文件目录结构如下:
```
Course_Design/
├── DecodeOnHaffmanCode/
│   ├── decode.h
│   └── decode.c
├── EncodeOnHaffmanTree/
│   ├── encode.h
│   └── encode.c
├── Helps/
│   └── help.h
│   └── help.c
├── HuffmanTreeBuild/
│   ├── build.c
│   └── build.h
├── Test/
│   ├── 1.pdf
│   ├── 2.pptx
│   ├── 3.png
│   ├── 4.mp3
│   ├── 5.mp4
│   └── 6.txt
├── main.c
├── script.sh
├── README.md
└── Makefile
```


利用哈夫曼编码进行信息通信可以大大提高信道利用率，缩短信息传输时间，降低传输成本。但是，这要求在发送端通过一个编码系统对待传数据预先编码，在接收端将传来的数据进行译码（复原）。试为这样的信息收发站写一个哈夫曼的编/译码器。

- 建立哈夫曼树：读入文件(*.souce)，统计文件中字符出现的频度，并以这些字符的频度作为权值，建立哈夫曼树。
- 编码：利用已建立好的哈夫曼树，获得各个字符的哈夫曼编码，并对正文进行编码，然后输出编码结果，并存入文件(*.code)中。
- 译码：利用已建立好的哈夫曼树将文件(x.code)中的代码进行译码，并输出译码结果，并存入文件(x.decode)中。
- 利用位操作，实现文件的压缩与解压。


## 设计思路

### 预期的命令如下:

```c
// 打印出帮助信息,命令行用法,可加参数
haff -h

// 压缩
haff -z 源文件名 -o 压缩文件名

// 解压
haff -u 压缩文件名 -o 解压后文件名
```

### 第一阶段思路
先实现一个简单的,后期功能往上加:
- `haff -z` 实现输出 `*.code`,这是一个文本文件,里面存放着 010101...

- `haff -u` 实现将 `*.code` 恢复成原来的样子


首先,将源文件变成 `*.code`后,这个文件要想在下次操作中恢复,必须包含的信息有:
- Haffman 编码;
- 根据 Haffman 编码将源文件得到的二进制编码.

解压的时候,首先找到 Haffman 字段,然后从文件开始的位置开始恢复文件.

现在的思路是,我用了一个额外的 `.haffmancode` 来存储哈夫曼编码,解码的时候将其反序列化早结构体中.很明显这样有一个缺陷,那就是要生成两个文件,一个`.haffmancode`,一个编码文本文件,因此必须得有一个 1.5阶段.


### 第 1.5 阶段思路
现在有了 `.haffmancode` 文件和 编码好的文本文件:
- 将编码好的文本文件编程成 二进制文件
- 将两个文件合成一个文件

哈夫曼编码文本文件,可以在生成的时候,直接生成二进制文件而不是文本文件.如果一个被压缩的文件 100MB,那么(中间)生成的文件大小可能能达到 800MB.800M的文本文件是不可接受的.

因此在生成编码文件的时候,直接将其输出成二进制文件最好.但是有一个问题比较棘手,那就是一个Byte的哈夫曼编码可能是 4bit, 7bit,这意味着需要建立一个缓冲池 unsigned long Buffer.当一个 01001 的哈夫曼编码生成时,Buffer=01001,此时有两种情况:

- 还会再有一个哈夫曼编码 01011,这时就可以凑一个完整的字节,写入文件,再写入00000000 ,意味着没有补0;
- 这是最后一个字节,需要补 000,形成一个完整的字节:01001000,写入文件,由于补了 3bit,那么得在最后将字节00000011 写入文件.


对于解压文件时候,仍然需要将这个二进制文件的 4 个字节读入一个缓冲区中,然后从缓冲区中拿到编码,进行匹配解密.

### 第二阶段思路

由于编码后的`*.code` 文件本质上是一个文本文件,其肯定比原文件大很多,那么我们肯定不能将这个文本文件保存起来用于传输.

因此必须将这个文本文件转化成一个二进制文件,就是将文本文件中的 8 个 01 字符当成一个字节写入二进制文件,写入的时候得保证内存对齐,因为不能保证 0101 文本文件的字符个数恰好是 8 的倍数,因此要在最后一个字符末尾补 若干0.

比如:01011,我们必须补成 01011000,这样就完美解决了内存对齐问题.

解码的时候,可以设定前 200 个字节为哈夫曼编码信息,从第 200 开始,就是文件编码信息,开始从这里进行解码.这样避免了使用魔数机制开始找开始的地方.

### 最后的思路

以下为写压缩文件的步骤:
- 写入 魔数 `0xdeadbeef`
- 写入 haffman code 大小
- 写入 Haffman Code
- 写入 文件大小
- 写入 文件编码
- 得到压缩文件

解压文件步骤:
- 检查魔数
- 得到 Haffman code 大小
- 反序列化 Haffman Code
- 拿到 文件大小信息
- 取出 文件编码
- 根据 Haffman Code 和 文件编码 得到目标文件

### 说明

本文件用的 自动化编译工具 make,也就是带有脑子的脚本解释工具,它会直接读取  `Makefile` 文件,完成编译.

本项目测试用的是 sh 脚本,解释器是 `sh` ,直接在在本 shell 中执行就好.子 shell 会需要权限,键入`chmod +x ./script` 就可以在子 shell 中运行了.


编译:
```bash
make
```

在本 shell 中运行:
```bash
. ./script.sh
```

然后就得到了测试信息:

```bash
ile: ./Test/1.pdf is zipping now!
file: ./Test/1.pdf zipped successed!                                   ] 0.00%
the rate of the zip is 0.99944
file: ./Test/2.pptx is zipping now!
file: ./Test/2.pptx zipped successed!                                  ] 0.00%
the rate of the zip is 1.01594
file: ./Test/3.png is zipping now!
file: ./Test/3.png zipped successed!                                   ] 0.00%
the rate of the zip is 1.00278
file: ./Test/4.mp3 is zipping now!
file: ./Test/4.mp3 zipped successed!                                   ] 0.00%
the rate of the zip is 0.99846
file: ./Test/5.mp4 is zipping now!
file: ./Test/5.mp4 zipped successed!===============================    ] 92.21%
the rate of the zip is 0.99829
file: ./Test/6.txt is zipping now!
file: ./Test/6.txt zipped successed!                                   ] 0.00%
the rate of the zip is 0.60989
file: ./Test/zipfile1.code is unzipping!
file: ./Test/zipfile1.code unzip successed!=======================     ] 90.12%
file: ./Test/zipfile2.code is unzipping!
file: ./Test/zipfile2.code unzip successed!======================      ] 88.70%
file: ./Test/zipfile3.code is unzipping!
file: ./Test/zipfile3.code unzip successed!==========================  ] 97.30%
file: ./Test/zipfile4.code is unzipping!
file: ./Test/zipfile4.code unzip successed!=======================     ] 90.54%
file: ./Test/zipfile5.code is unzipping!
...
```

某些文件压缩率很大,这很正常,因为它本身就是压缩文件(pdf, pptx, mp3, png),但对于文本文件有着很好的压缩效果.


