FROM python:latest

RUN mkdir -p ~/dockers/
WORKDIR ~/dockers#/usr/src/app/

ADD ./requirements.txt ./requirements.txt
RUN pip3 install -r requirements.txt
ADD . .

CMD ["python3", "l1.py"]
