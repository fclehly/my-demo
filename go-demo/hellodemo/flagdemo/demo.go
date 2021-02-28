package flagdemo

import (
	"flag"
	"fmt"
)

func FlagDemo() {
	app := flag.String("app", "default-app", "enter your app id")
	var version int
	flag.IntVar(&version, "version", 0, "input your version")
	flag.Parse()
	fmt.Printf("app.id=%s version=%d\n", *app, version)
	fmt.Printf("flag.args=%v\n", flag.Args())
	fmt.Printf("flag.arg=%v\n", flag.Args())
	fmt.Printf("flag.n.arg=%v\n", flag.NArg())
	fmt.Printf("flag.n.flag=%v\n", flag.NFlag())
}
