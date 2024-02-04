# Interview task

## build docker image
```docker build -t interview_image . ```

## run image
### mount src code in image or clone it inside
```docker run -it -v ${PWD}:/src interview_image```

## inside image
```cd /src```

## install dependecies with conan
```conan install .. --build=missing```

## configure project
```cmake .. -G Ninja```

## build project
```cmake --build . --target all```

## run tests
```cmake --build . --target RunAllTests```

## clang-tidy for code quality
```
cd ..
```

```
mkdir buildCodeInspection && cd buildCodeInspection
```

```
conan install .. --build=missing
```

```
cmake .. -G Ninja -DPERFORM_CODE_INSPECTION=ON
```

```
cmake --build . --target all
```
