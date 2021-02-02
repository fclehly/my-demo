package main

import (
	"fmt"
	"hellodemo/helloworld"
	"hellodemo/timedemo"
)

func main() {
	fmt.Println("helloworld")
	helloworld.Print1(66)
	timedemo.TimeDemo()
}
