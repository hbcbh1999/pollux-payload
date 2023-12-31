FROM ubuntu:latest AS builder

# Update Ubuntu Software repository
RUN apt-get update && apt-get -y install \
    cmake \
    make  \
    g++ \
    libtbb-dev \
    protobuf-compiler-grpc \
    libgrpc++-dev

WORKDIR /pollux-payload
COPY cmake cmake
COPY src src
COPY thirdparty thirdparty
COPY CMakeLists.txt .
RUN cmake . && make -j$(nproc)

FROM polluxio/pollux:latest AS pollux-payload-examples
RUN apt-get update && apt-get -y install libgrpc++ openssh-server libtbb-dev
RUN mkdir /var/run/sshd
RUN sed -ri 's/^#?PermitRootLogin\s+.*/PermitRootLogin yes/' /etc/ssh/sshd_config

#ENV GRPC_TRACE=all
#ENV GRPC_VERBOSITY=DEBUG
#ENV GRPC_GO_LOG_VERBOSITY_LEVEL=99
#ENV GRPC_GO_LOG_SEVERITY_LEVEL=info
WORKDIR /root
COPY --from=builder /pollux-payload/src/c++/examples/test/pollux-payload-test ./pollux-payload-test
COPY --from=builder /pollux-payload/src/c++/examples/pso/pollux-payload-pso ./pollux-payload-pso
EXPOSE 22 
#For Pollux Communication
EXPOSE 50000
