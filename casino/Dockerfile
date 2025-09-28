FROM python:3.12

RUN apt-get update
RUN apt-get install -y socat
RUN rm -rf /var/lib/apt/lists/*

RUN mkdir -p /opt/chal
WORKDIR /opt/chal

COPY flag.txt src.py ./

RUN adduser chal
USER chal
CMD socat -v -T60 tcp-listen:1337,fork,reuseaddr system:"python3 src.py 2>&1"
