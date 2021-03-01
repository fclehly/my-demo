package main

import (
	"fmt"
	// "hellodemo/helloworld"
	// "hellodemo/timedemo"
	// "hellodemo/flagdemo"
	// "hellodemo/logdemo"
	// "hellodemo/filedemo"
	"hellodemo/nethttpdemo"
)

func main() {
	fmt.Println("---- start ----")
	// timedemo.TimeDemo()
	// flagdemo.FlagDemo()
	// logdemo.LogDemo()
	// filedemo.FileReadDemo()
	nethttpdemo.HttpGetDemo()
	fmt.Println("----  end  ----")
}
