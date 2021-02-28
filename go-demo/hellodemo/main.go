package main

import (
	"fmt"
	// "hellodemo/helloworld"
	// "hellodemo/timedemo"
	"hellodemo/flagdemo"
)

func main() {
	fmt.Println("---- start ----")
	// timedemo.TimeDemo()
	flagdemo.FlagDemo()
	fmt.Println("----  end  ----")
}
