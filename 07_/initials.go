package main

import "os"
import "fmt"
import "bufio"
import "strings"
import "bytes"

func getInput() string {

	reader := bufio.NewReader(os.Stdin)
	fmt.Print("Enter Your full name : ")
	text, _ := reader.ReadString('\n')
	return text
}

func genInitials(inputstring string) string {

	words := strings.Split(strings.Title(inputstring), " ")
	var buffer bytes.Buffer
	for _, v := range words {
		buffer.WriteString(string(v[0]))
	}
	return buffer.String()
}

func main() {

	fullname := getInput()
	initials := genInitials(fullname)
	fmt.Println("Initials : ", initials)
}
