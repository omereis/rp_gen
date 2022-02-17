docker rm -f rp_gen
docker build --rm -f gen.dockerfile -t rp_gen .
rem docker run -it -d -h rp_gen --link rsa --name rp_gen -p 5005:5005 rp_gen
docker run -it -d -h rp_gen --name rp_gen rp_gen
rem docker run -it -d -h rp_gen --name rp_gen -v g:/home/gen/sim rp_gen
rem docker run -it -d --name docker_refsrv
docker exec -it rp_gen bash
