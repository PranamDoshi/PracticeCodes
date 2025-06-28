package main

import (
	"fmt"
	"math"
)

type ErrNegativeSqrt float64

func (e ErrNegativeSqrt) Error() string {
	return fmt.Sprintf("cannot Sqrt negative number: %g", e)
}

func Sqrt(x float64) (z_new float64, e error) {
	// isChanging:= func(z_old, z_new float64) bool {
	// 	if z_old - z_new <= 1e-3 {
	// 		return false
	// 	} else if z_old - z_new > 0 {
	// 		return true
	// 	} else {
	// 		return false
	// 	}
	// }
	if x < 0 {
		e = ErrNegativeSqrt(x)
		return 0, e
	}

	reduceZ := func(z, x float64) float64 {
		z -= (math.Pow(z, 2) - x) / (2 * z)
		return z
	}

	z_old := x
	z_new = reduceZ(z_old, x)
	// fmt.Println("%f - %f", z_old, z_new)

	for math.Abs(z_old-z_new) > 1e-3 {
		z_old = z_new
		z_new = reduceZ(z_old, x)
		// fmt.Println("%f - %f", z_old, z_new)
	}
	// fmt.Println(math.Pow(z_new, 2))
	return
}

func main() {
	fmt.Println(Sqrt(2))
	fmt.Println(Sqrt(-2))
}
