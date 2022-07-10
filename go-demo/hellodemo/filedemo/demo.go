package filedemo

import (
	"bufio"
	"io"
	"io/ioutil"
	"log"
	"os"
	"time"
)

func FileDemo() {
	file, err := os.OpenFile("/Users/fwz/Workspace/my-demo/go-demo/hellodemo/test.txt", os.O_CREATE|os.O_RDWR, 0666)
	if err != nil {
		log.Panicf("open file error: %v\n", err)
		return
	}
	defer file.Close()
	s := "abc" + time.Now().String()
	file.Write([]byte(s))
	file.WriteString(s)
	var temp = make([]byte, 128)
	var content []byte
	for {
		n, err := file.Read(temp)
		if err == io.EOF {
			log.Println("read file end")
			break
		}
		if err != nil {
			log.Panicf("read file fail: %v\n", err)
			break
		}
		content = append(content, temp[:n]...)
	}
	log.Println(string(content))
}

func BufioDemo() {
	file, err := os.Open("/Users/fwz/Workspace/my-demo/go-demo/hellodemo/main.go")
	if err != nil {
		log.Panicf("open file error: %v\n", err)
		return
	}
	defer file.Close()
	reader := bufio.NewReader(file)
	for {
		line, err := reader.ReadString('\n')
		if err == io.EOF {
			log.Println("read file end")
			break
		}
		if err != nil {
			log.Panicf("read file fail: %v\n", err)
			break
		}
		log.Println(line)
	}

}

func IoutilDemo() {
	content, err := ioutil.ReadFile("/Users/fwz/Workspace/my-demo/go-demo/hellodemo/main.go")
	if err != nil {
		log.Panicf("read file fail: %v\n", err)
		return
	}
	log.Println(string(content))
}
