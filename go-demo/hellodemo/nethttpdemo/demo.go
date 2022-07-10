package nethttpdemo

import (
	"io/ioutil"
	"log"
	"net/http"
)

func HttpGetDemo() {
	resp, err := http.Get("http://www.baidu.com")
	if err != nil {
		log.Panicln(err)
		return
	}
	defer resp.Body.Close()
	log.Println(resp)
	body, err := ioutil.ReadAll(resp.Body)
	if err != nil {
		log.Panicln(err)
		return
	}
	log.Println(string(body))
}
