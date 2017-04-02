package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"strconv"
	"strings"
)

func getInput() string {
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("plaintext: ")
	text, _ := reader.ReadString('\n')
	return text
}

func shiftChar(letter string, k int) string {
	a := int(letter[0]) + k
	if a > 'z' {
		return string(a - 26)
	} else if a < 'a' {
		return string(a + 26)
	}
	return string(a)
}

func encodeString(text string, k int) string {
	var buffer bytes.Buffer
	for _, v := range text {
		buffer.WriteString(shiftChar(string(v), k))
	}
	return buffer.String()
}

func main() {

	if len(os.Args) == 2 {
		k, _ := strconv.Atoi(os.Args[1])
		text := strings.TrimRight(getInput(), "\n\r")
		result := encodeString(text, k)
		fmt.Println("ciphertext: ", result)
	} else {
		fmt.Println("Oops!  Usage: ./caesar k")
	}

}
