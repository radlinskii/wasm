package server

import (
	"math"
	"math/rand"
)

func init() {
	// var sphereFunc = fitnessFunction{ID: sphere, Dimensions: 10, MinValue: 0, MaxValue: 10000000000}
	var michalewiczFunc = fitnessFunction{ID: michalewicz, Dimensions: 2, MinValue: 0, MaxValue: math.Pi}
	// var bealeFunc = fitnessFunction{ID: beale, Dimensions: 2, MinValue: -4.5, MaxValue: 4.5}

	fitnessFunc = michalewiczFunc
	populationLength = 100
	maxNumOfGenerations = 20
}

var fitnessFunc fitnessFunction
var populationLength int
var genCount = 0
var maxNumOfGenerations = 100

type fitnessFuncType int

const (
	sphere fitnessFuncType = iota
	michalewicz
	beale
)

func (f fitnessFuncType) String() string {
	return []string{"sphere", "michalewicz", "beale"}[f]
}

// fitnessFunction is a enum of available goal functions
type fitnessFunction struct {
	ID         fitnessFuncType
	Dimensions int
	MinValue   float64
	MaxValue   float64
}

// individual is a vector of elements
type individual []float64

// population is a vector of Individuals
type population []individual

func getRandF64(min, max float64) float64 {
	return min + rand.Float64()*(max-min)
}

func populate(length int, f fitnessFunction) population {
	var population population

	for i := 0; i < length; i++ {
		vector := individual{}
		for j := 0; j < f.Dimensions; j++ {
			vector = append(vector, getRandF64(f.MinValue, f.MaxValue))
		}
		population = append(population, vector)
	}

	return population
}
