package main

import (
	"bufio"
	"bytes"
	"fmt"
	"os"
	"strings"
)

func getInput() string {
	reader := bufio.NewReader(os.Stdin)
	fmt.Print("plaintext: ")
	text, _ := reader.ReadString('\n')
	return text
}

func getShiftDistance(key_string string, pos int) int {
	pz := pos % (len(key_string))
	cc := key_string[pz] - 'a'
	return int(cc)
}

func shiftChar(letter string, key string, pos int) string {
	a := int(letter[0]) + getShiftDistance(key, pos)
	if a > 'z' {
		return string(a - 26)
	} else if a < 'a' {
		return string(a + 26)
	}
	return string(a)
}

func encodeString(text string, k string) string {
	var buffer bytes.Buffer
	var not_alphabet_cnt int
	for i, v := range text {
		if v >= 'A' && v <= 'z' {
			buffer.WriteString(shiftChar(string(v), k, i-not_alphabet_cnt))
		} else {
			not_alphabet_cnt++
		}
	}
	return buffer.String()
}

func main() {

	if len(os.Args) == 2 {
		key := os.Args[1]
		text := strings.TrimRight(getInput(), "\n\r")
		result := encodeString(text, key)
		fmt.Println("ciphertext: ", result)
	} else {
		fmt.Println("Oops!  Usage: ./vigenere k")
	}

}
