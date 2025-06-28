package main

import (
	"fmt"
	"image"
	"image/color"

	"golang.org/x/tour/pic"
)

func Pic(dx, dy int) [][]uint8 {
	var pic = make([][]uint8, dx)
	for i := range pic {
		pic[i] = make([]uint8, dy)
	}

	for x := 0; x < dx; x++ {
		for y := 0; y < dy; y++ {
			pic[x][y] = uint8((x + y) * 2)
		}
	}
	return pic
}

func printPic(pic [][]uint8) {
	for i := range pic {
		for j := range pic[i] {
			fmt.Printf("%d ", pic[i][j])
		}
		fmt.Println("\n")
	}
}

type Image struct {
	width, height int
}

func (img Image) ColorModel() color.Model {
	return color.RGBA64Model
}

func (img Image) Bounds() image.Rectangle {
	return image.Rect(0, 0, img.width, img.height)
}

func (img Image) At(x, y int) color.Color {
	v := uint8(x * y)
	return color.RGBA{v, v, 255, 255}
}

func main() {
	// pic.Show(Pic)
	// printPic(Pic(5, 5))

	img := Image{5, 5}
	fmt.Println(img.ColorModel())
	fmt.Println(img.Bounds())
	fmt.Println(img.At(2, 3))

	pic.ShowImage(img)
}
