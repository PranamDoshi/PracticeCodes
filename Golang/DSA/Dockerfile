# Build stage
FROM golang:1.24.4-alpine3.21 AS builder

ENV MOD_NAME="myapp"

WORKDIR /app

# Copy go.mod and go.sum if present
COPY go.mod ./
# COPY go.sum ./
# RUN go mod download

# Copy the rest of the source code
COPY . .

# Build the Go binary
RUN CGO_ENABLED=0 GOOS=linux go build -o ${MOD_NAME}

# Final stage
FROM alpine:3.21
WORKDIR /root/
COPY --from=builder /app/${MOD_NAME} .

ENTRYPOINT ["./myapp"]
