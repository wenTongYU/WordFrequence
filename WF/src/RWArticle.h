
/**
 * 这是个用于管理读写文章的功能类
 * 
 * 
 * Author : YU_IT
 * Time : 2019年10月22日 
*/

#pragma once

#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include <sstream>
#include <iostream>

namespace Wf
{
    enum WfIOFlags
    {
        Wf_in     = std::ios_base::in,
        Wf_out    = std::ios_base::out,
        Wf_ate    = std::ios_base::ate,
        Wf_app    = std::ios_base::app,
        Wf_trunc  = std::ios_base::trunc,
        Wf_binary = std::ios_base::binary
    };

    enum WfRWFileFlags
    {
        Wf_Read = 20,
        Wf_Write
    };

    class WfIO : public std::fstream
    {
    private:
        // 按文章段落存取
        std::vector<std::string> m_fileContent;
        void _init(const char * fileName, WfIOFlags flags, WfRWFileFlags rw);
    public:
        // default constructor
        WfIO() {};
        // default destructor
        ~WfIO();
        // delete copy constructor
        WfIO(const WfIO& ) = delete;

        // 将这两个构造函数标记为显式的，通常忽略默认构造函数
        explicit WfIO(const char* fileName, WfIOFlags flags);
        explicit WfIO(const std::string fileName, WfIOFlags flags);

        /**
         * @breif 通过段落的标识获取相应的文本内容
         * @param0 index : 段落标识（顺序排列）
         * @return 返回一个string对象的引用（因为文本内容较多，拷贝会花费较多时间，所以使用引用）
        */
        const std::string& getFileContentByParagraph(unsigned int index) const;

        /**
         * @breif 获取所有的文本内容 【弃用的】
         * @param0 buffer : 可以为空指针，函数来分配内存；如果不是空指针则必须包含足够的内存空间，用于存取文章的所有内容
         * @noreturn 
        */
		[[deprecated]]
        void getAllFileContent(char* buffer) const;

        /**
         * @breif 将内容输出到文件
         * @param0 fileName : 标识输出的文件名，当文件不存在的时候创建一个文件
         * @param1 buffer : 标识要输出的内容
         * @param2 output : 标识
        */
        void outputFile(const char* fileName, const std::string& buffer);
    };

    WfIO::~WfIO()
    {
        if(!m_fileContent.empty())
            m_fileContent.clear();
        if(is_open())
            close();
    }

    void WfIO::_init(const char* fileName, WfIOFlags flags, WfRWFileFlags rw)
    {
        // set exception bits
        exceptions(ios_base::badbit | ios_base::failbit);
        try{
            // read file in
            open(fileName, flags);
            if(rw == Wf_Read)
            {
                std::string tmpbuf;
                int j = 0;
                while(!eof())
                {
                    std::getline(*this, tmpbuf, '\n');
                    // seekg(_s, tmpbuf.size());
                    m_fileContent.push_back(tmpbuf);
                    printf("The %d paragraph has been read into the buffer.\n", j++);
                }
            }else if(rw == Wf_Write)
            {
                
            }
        }
        catch(std::ios_base::failure e)
        {
            printf(e.what());
        }

    }

    WfIO::WfIO(const char* fileName, WfIOFlags flags)
    {
        _init(fileName, flags, Wf_Read);
        close();
    }

    WfIO::WfIO(std::string fileName, WfIOFlags flags)
    {
        _init(fileName.c_str(), flags, Wf_Read);
        close();
    }

    const std::string& WfIO::getFileContentByParagraph(unsigned int index) const
    {
        if(index > m_fileContent.size())
        {
            printf("The index is over the counts of paragraph");
            return std::forward<std::string>(std::string());
        }
        return m_fileContent.at(index);
    }

    void WfIO::getAllFileContent(char* buf) const
    {
       
    }

    void WfIO::outputFile(const char* fileName, const std::string& buffer)
    {
        _init(fileName, (Wf::WfIOFlags)(Wf_out | Wf_trunc), Wf_Write);
		std::stringstream ss(buffer);
		
		write(buffer.c_str(), buffer.size());
		
		flush();
        close();
    }

	
}