namespace :build do
  desc "builds lib"
  task :run do  
    sh %{cd ext/src && gcc -c ABELCommObject.c}
    sh %{cd ext/src && gcc -shared -W1 -o ABELCommObject.so ABELCommObject.o -labplc5}
    sh %{cp ext/src/*.so lib/abel/}
  end
end

namespace :gem do
  desc "build gem"
  task :build => :'build:run' do
    sh %{gem build abel.gemspec}
  end
end

desc "builds lib"
task :default => :build

desc "builds lib builds gem installs gem"
task :install => :'gem:build' do
  sh %{sudo gem i ./*.gem}
end

