class JemWorker
  include Sidekiq::Worker
  include SidekiqStatus::Worker

  def perform(*args)
    # Do something
    self.total = 100
    100.times do |i|
    	sleep 1
    	at i
    end
    at 100
  end
end
